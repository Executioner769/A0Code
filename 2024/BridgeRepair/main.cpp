#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Only Two Operators [+,*]
// [Finished in 554ms]
bool solveTwoOps(ll prev, int idx, vector<ll>& nums, ll value, map<pair<ll,int>,int>& dp) {
	if(idx == nums.size()) {
		return prev == value;
	}
	
	if(dp[{prev,idx}] != 0) {
		return dp[{prev,idx}];
	}
	
	bool addition = false;
	ll add = prev + nums[idx];
	if(add <= value) {
		addition = solveTwoOps(add,idx+1,nums,value,dp);
	}
	
	bool multiplication = false;
	ll mul = prev * nums[idx];
	if(mul <= value) {
		multiplication = solveTwoOps(mul,idx+1,nums,value,dp);
	}
	
	return dp[{prev,idx}] = (addition || multiplication);
}

// Only Three Operators [+,*,||]
// [Finished in 4.6s]
bool solveThreeOps(ll prev, int idx, vector<ll>& nums, vector<string>& numsStr, const ll value, map<pair<ll,int>,int>& dp) {
	if(idx == nums.size()) {
		return prev == value;
	}
	
	if(dp[{prev,idx}] != 0) {
		return dp[{prev,idx}];
	}
	
	bool concatenation = false;
	ll concat = prev;
	for(int ch = 0; ch < numsStr[idx].length(); ++ch) {
		concat = concat * 10 + (numsStr[idx][ch] - '0');
		if(concat > value) break;
	}
	if(concat <= value) {
		concatenation = solveThreeOps(concat,idx+1,nums,numsStr,value,dp);
	}
	
	bool addition = false;
	ll add = prev + nums[idx];
	if(add <= value) {
		addition = solveThreeOps(add,idx+1,nums,numsStr,value,dp);
	}
	
	bool multiplication = false;
	ll mul = prev * nums[idx];
	if(mul <= value) {
		multiplication = solveThreeOps(mul,idx+1,nums,numsStr,value,dp);
	}
	
	return dp[{prev,idx}] = (concatenation || addition || multiplication);
}

bool solveEquation2(ll value, vector<ll>& nums) {
	map<pair<ll,int>,int> dp;
	return solveTwoOps(nums[0], 1, nums, value, dp);
}

bool solveEquation3(ll value, vector<ll>& nums, vector<string>& numsStr) {
	map<pair<ll,int>,int> dp;
	return solveThreeOps(nums[0], 1, nums, numsStr, value, dp);
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	ll calibration2 = 0, calibration3 = 0;
	
	string str;
	ll value;
	
	for(string line; getline(cin,line);) {
		istringstream iss(line);
		vector<ll> nums;
		vector<string> numsStr;
		while(iss >> str) {
			if(str.back() == ':') {
				str.pop_back();
				value = stoll(str);
				continue;
			}
			nums.push_back(stoll(str));
			numsStr.push_back(str);
		}
		
		if(solveEquation2(value, nums)) {
			calibration2 += value;
		}
		
		if(solveEquation3(value, nums, numsStr)) {
			calibration3 += value;
		}
	}
	
	cout << calibration2 << "\n";
	cout << calibration3 << "\n";

	return 0;
}

// Together
// [Finished in 4.8s]