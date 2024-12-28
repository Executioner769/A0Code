#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool solve(int s, string& design, unordered_set<string>& towels, vector<int>& dp) {
	if(s == design.length()) {
		return true;
	}
	
	if(dp[s] != -1) return dp[s];
	
	string temp = "";
	for(int k = s; k < design.length(); ++k) {
		temp += design[k];
		if(towels.count(temp) != 0) {
			if(solve(k+1,design,towels,dp)) {
				return dp[s] = true;
			}
		}
	}
	
	return dp[s] = false;
}

int main(int argc, char const *argv[]) {
	
	string line;
	getline(cin,line);
	
	unordered_set<string> towels;
	string towel;
	for(auto &ch: line) {
		if(ch == ',') {
			towels.insert(towel);
			towel = "";
			continue;
		}
		if(ch != ' ') {
			towel += ch;
		}
	}
	towels.insert(towel);
	
	int total = 0;
	for(string design;getline(cin,design);) {
		if(design.size() == 0) continue;
		vector<int> dp(design.length()+1, -1);
		bool isPossible = solve(0,design,towels,dp);
		if(isPossible) total++;
	}
	
	cout << total;
	
	return 0;
}