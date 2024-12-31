#include <bits/stdc++.h>
using namespace std;


bool debug = false;

bool verfiyXOR(string,int,map<string,vector<string>>&);
bool verifyDCarry(string,int,map<string,vector<string>>&);
bool verifyReCarry(string,int,map<string,vector<string>>&);
bool verifyCBit(string,int,map<string,vector<string>>&);
bool verifyZBit(string,int,map<string,vector<string>>&);
bool verify(int, map<string,vector<string>>&);

int calculateValue(string wire, map<string, int>& values, map<string,vector<string>>& adj) {
	if(values.find(wire) != values.end()) {
		return values[wire];
	}

	int value;
	auto& vec = adj[wire];
	string wire1 = vec[0], operation = vec[1] , wire2 = vec[2];
	if(operation == "AND") {
		value = calculateValue(wire1, values, adj) & calculateValue(wire2, values, adj);
	} else if(operation == "OR") {
		value = calculateValue(wire1, values, adj) | calculateValue(wire2, values, adj);
	} else if(operation == "XOR") {
		value = calculateValue(wire1, values, adj) ^ calculateValue(wire2, values, adj);
	}

	return values[wire] = value;
}

string getStr(priority_queue<string>& wires, map<string, int>& values) {
	string str;
	while(!wires.empty()) {
		string wire = wires.top(); wires.pop();
		// printf("%s %d\n", wire.c_str(), values[wire]);
		str += (values[wire] + '0');
	}
	return str;
}

string add(string x, string y) {
	string z;
	int c = 0;
	int i = x.length()-1, j = y.length()-1;
	while(i >= 0 || j >= 0) {
		int xbit = 0, ybit = 0;
		if(i >= 0) xbit = (x[i--] == '1');
		if(j >= 0) ybit = (y[j--] == '1');

		// odd ones yeild one
		int zbit = c ^ (xbit ^ ybit);
		// either two ones or three ones set carry one
		int nc = (xbit & ybit) | (c & (xbit ^ ybit));
		c = nc;
		z.push_back(zbit+'0');
	}
	if(c) {
		z.push_back(c+'0');
	}
	reverse(z.begin(), z.end());
	return z;
}

string makeWire(char ch, int bit) {
	string wire;
	wire += ch;
	wire += bit/10 + '0';
	wire += bit%10 + '0';
	return wire;
}

string pprint(string wire, map<string,vector<string>>& adj, int depth=0) {
	// Intial Wire
	if(wire.front() == 'x' || wire.front() == 'y') {
		return string(depth*2,' ') + wire;
	}
	auto& vec = adj[wire];
	string wire1 = vec[0], operation = vec[1] , wire2 = vec[2];
	return string(depth*2,' ') + operation + " (" + wire + ")\n" + pprint(wire1,adj,depth+1) + "\n" + pprint(wire2,adj,depth+1);
}

bool verfiyXOR(string wire, int bit, map<string,vector<string>>& adj) {
	if(debug) printf("Verify XOR: %s %d\n", wire.c_str(), bit);
	auto& vec = adj[wire];
	string x = vec[0], op = vec[1] , y = vec[2];
	if(op != "XOR") return false;
	if(x > y) swap(x,y);
	return (x == makeWire('x',bit) and y == makeWire('y',bit));
}

bool verifyDCarry(string wire, int bit, map<string,vector<string>>& adj) {
	if(debug) printf("Verify Direct Carry: %s %d\n", wire.c_str(), bit);
	auto& vec = adj[wire];
	string x = vec[0], op = vec[1] , y = vec[2];
	if(op != "AND") return false;
	if(x > y) swap(x,y);
	return (x == makeWire('x',bit) and y == makeWire('y',bit));
}

bool verifyReCarry(string wire, int bit, map<string,vector<string>>& adj) {
	if(debug) printf("Verify Direct Carry: %s %d\n", wire.c_str(), bit);
	auto& vec = adj[wire];
	string x = vec[0], op = vec[1] , y = vec[2];
	if(op != "AND") return false;
	return (verfiyXOR(x,bit,adj) and verifyCBit(y,bit,adj)) or (verfiyXOR(y,bit,adj) and verifyCBit(x,bit,adj));
}

bool verifyCBit(string wire, int bit, map<string,vector<string>>& adj) {
	if(debug) printf("Verify Carry Bit: %s %d\n", wire.c_str(), bit);
	auto& vec = adj[wire];
	string x = vec[0], op = vec[1] , y = vec[2];
	if(x > y) swap(x,y);
	// The Carry Logic fo the First Carry Bit
	if(bit == 1) {
		if(op != "AND") return false;
		return ((x == "x00") and (y == "y00"));
	}
	// Direct Carry OR Re Carry
	if(op != "OR") return false;
	return (verifyDCarry(x,bit-1,adj) and verifyReCarry(y,bit-1,adj)) or (verifyDCarry(y,bit-1,adj) and verifyReCarry(x,bit-1,adj));
}

bool verifyZBit(string wire, int bit, map<string,vector<string>>& adj) {
	if(debug) printf("Verify Bit: %s %d\n", wire.c_str(), bit);
	auto& vec = adj[wire];
	string x = vec[0], op = vec[1] , y = vec[2];
	if(x > y) swap(x,y);
	if(op != "XOR") return false;
	if(bit == 0) return ((x == "x00") and (y == "y00"));
	// zBit == (xBit ^ yBit) ^ cBit || cBit ^ (xBit ^ yBit)
	return (verfiyXOR(x,bit,adj) and verifyCBit(y,bit,adj)) or (verfiyXOR(y,bit,adj) and verifyCBit(x,bit,adj));
}

bool verify(int bit, map<string,vector<string>>& adj) {
	assert(bit < 100);
	return verifyZBit(makeWire('z',bit), bit, adj);
}

int main(int argc, char const *argv[]) {

	string line;
	map<string, int> values;
	priority_queue<string> xwires, ywires;
	while(getline(cin,line)) {
		if(line.size() == 0) break;
		int pos = line.find(":");
		if(pos != string::npos) {
			int value = line.back() - '0';
			string wire = line.substr(0,pos);
			values[wire] = value;

			 if(wire.front() == 'x') {
				xwires.push(wire);
			} else if(wire.front() == 'y') {
				ywires.push(wire);
			}
		}
	}

	map<string,vector<string>> adj;

	while(getline(cin,line)) {
		istringstream iss(line);
		string wire1, wire2, operation, _skip, wire3;

		iss >> wire1;
		iss >> operation;
		iss >> wire2;
		iss >> _skip;
		iss >> wire3;

		adj[wire3] = vector<string>{wire1, operation, wire2};
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

	// string zstr, xstr, ystr;

	// xstr = getStr(xwires, values);
	// printf("%46s\n", xstr.c_str());

	// ystr = getStr(ywires, values);
	// printf("%46s\n", ystr.c_str());

	// puts("");

	// string sum = add(xstr,ystr);
	// printf("%46s\n", sum.c_str());

	// zstr = getStr(zwires, values);
	// printf("%46s\n", zstr.c_str());

	// unsigned long long number = stoull(zstr,0,2);
	// printf("%lld\n", number);

	int bit = 0;

	while(bit < 46) {
		if(verify(bit, adj) != true) {
			break;
		}
		bit += 1;
	}
	printf("Failed for %s wire\n", makeWire('z',bit).c_str());

	// hnd, z09
	// tdv, z16
	// bks, z23
	// tjp, nrn

	vector<string> swaps = {"hnd","z09","tdv","z16","bks","z23","tjp","nrn"};
	sort(swaps.begin(), swaps.end());
	for(auto& wire: swaps) {
		printf("%s,", wire.c_str());
	}

	return 0;
}
