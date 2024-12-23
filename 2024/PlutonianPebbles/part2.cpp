#include <bits/stdc++.h>
using namespace std;

#define ll long long

// {stoneStr,blink} --> stones Count
map<pair<string,int>,ll> dp;

ll solve(ll stone, int blinks) {
	if(blinks == 0) return 1;
	
	string stoneStr = to_string(stone);
	
	if(dp.find({stoneStr,blinks}) != dp.end()) {
		return dp[{stoneStr,blinks}];
	}
	
	if(stone == 0) {
		return dp[{stoneStr,blinks}] = solve(1,blinks-1);
	}
	
	if(stoneStr.length() % 2 == 0) {
		string s1 = stoneStr.substr(0,stoneStr.length() / 2);
		string s2 = stoneStr.substr(stoneStr.length() / 2);
		
		ll left = solve(stoll(s1),blinks-1);
		ll right = solve(stoll(s2),blinks-1);
		
		return dp[{stoneStr,blinks}] = left + right;
	}
	
	return dp[{stoneStr,blinks}] = solve(stone*2024, blinks-1);
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	int n = 8;
	vector<ll> stones(n);
	for(int i = 0; i < n; i++) {
		cin >> stones[i];
	}
	
	int blinks = 75;
	ll totalStones = 0;
	
	for(auto stone: stones) {
		totalStones += solve(stone,blinks);
	}
	
	cout << totalStones;

	return 0;
}