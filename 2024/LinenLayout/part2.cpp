#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll solve(int s, string& design, unordered_set<string>& towels, vector<ll>& dp) {
	if(s == design.length()) {
		return 1;
	}
	
	if(dp[s] != -1) return dp[s];
	
	string temp = "";
	ll ways = 0;
	for(int k = s; k < design.length(); ++k) {
		temp += design[k];
		if(towels.count(temp) != 0) {
			ways += solve(k+1,design,towels,dp);
		}
	}
	
	return dp[s] = ways;
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
	
	ll totalWays = 0;
	for(string design;getline(cin,design);) {
		if(design.size() == 0) continue;
		vector<ll> dp(design.length()+1, -1);
		ll ways = solve(0,design,towels,dp);
		totalWays += ways;
	}
	
	cout << totalWays;
	
	return 0;
}