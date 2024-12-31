#include <bits/stdc++.h>
using namespace std;

int calculateValue(string wire, map<string, int>& values, map<string, vector<vector<string>>>& adj) {
	if(values.find(wire) != values.end()) {
		return values[wire];
	}

	int value;
	for(auto& vec: adj[wire]) {
		string wire1 = vec[0], operation = vec[1] , wire2 = vec[2];
		if(operation == "AND") {
			value = calculateValue(wire1, values, adj) & calculateValue(wire2, values, adj);
		} else if(operation == "OR") {
			value = calculateValue(wire1, values, adj) | calculateValue(wire2, values, adj);
		} else if(operation == "XOR") {
			value = calculateValue(wire1, values, adj) ^ calculateValue(wire2, values, adj);
		}
	}
	return values[wire] = value;
}

int main(int argc, char const *argv[]) {

	string line;
	map<string, int> values;
	while(getline(cin,line)) {
		if(line.size() == 0) break;
		int pos = line.find(":");
		if(pos != string::npos) {
			int value = line.back() - '0';
			string wire = line.substr(0,pos);
			values[wire] = value;
		}
	}

	map<string, vector<vector<string>>> adj;

	while(getline(cin,line)) {
		istringstream iss(line);
		string wire1, wire2, operation, _skip, wire3;

		iss >> wire1;
		iss >> operation;
		iss >> wire2;
		iss >> _skip;
		iss >> wire3;

		adj[wire3].push_back({wire1, operation, wire2});
	}

	priority_queue<string> zwires;

	for(auto pr: adj) {
		string wire = pr.first;

		if(values.find(wire) == values.end()) {
			calculateValue(wire, values, adj);
		}

		if(wire.front() == 'z') {
			zwires.push(wire);
		}
	}

	string zstr;
	while(!zwires.empty()) {
		string wire = zwires.top(); zwires.pop();
		// printf("%s %d\n", wire.c_str(), values[wire]);
		zstr += (values[wire] + '0');
	}

	printf("%s\n", zstr.c_str());
	unsigned long long number = stoull(zstr,0,2);
	printf("%lld\n", number);

	return 0;
}
