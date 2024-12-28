#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 16777216;

void mixAndPrune(ll& secretNumber,const ll& number) {
	// Mix
	secretNumber ^= number;
	// Prune
	secretNumber %= MOD;
}

void nextSecretNumber(ll& secretNumber) {
	// Step1
	ll result = secretNumber * 64;
	mixAndPrune(secretNumber, result);
	
	// Step2
	result = secretNumber / 32;
	mixAndPrune(secretNumber, result);
	
	// Step3
	result = secretNumber * 2048;
	mixAndPrune(secretNumber, result);
}

void getNthSecretNumber(ll& secretNumber, vector<int>& bananas, map<queue<int>,int>& mp, int n) {
	string sec = to_string(secretNumber);
	int prevPrice = sec.back() - '0', currentPrice = 0;
	
	queue<int> q;
	set<queue<int>> st;
	
	for(int i = 1; i <= n; ++i) {
		nextSecretNumber(secretNumber);
		sec = to_string(secretNumber);
		currentPrice = sec.back() - '0';

		q.push(currentPrice - prevPrice);
		
		if(q.size() > 4) {
			q.pop();
		}
		
		if(q.size() == 4) {
			// First Time
			if(mp.find(q) == mp.end()) {
				mp[q] = bananas.size();
				bananas.push_back(currentPrice);
			} else if(st.find(q) == st.end()) {
				// Not First Time but from different buyer
				int idx = mp[q];
				bananas[idx] += currentPrice;
			}
			
			// Add to buyers' set 
			st.insert(q);
		}
		
		prevPrice = currentPrice;
	}
}

// Not at all efficient
// [Finished in 27.0s]
int main(int argc, char const *argv[]) {
	
	string line;
	ll secretNumber;

	int n = 2000;
	
	vector<int> bananas;
	
	map<queue<int>,int> mp;
	while(getline(cin,line)) {
		secretNumber = stoll(line);
		getNthSecretNumber(secretNumber,bananas,mp,n);
	}
	
	int maxBananas = *max_element(bananas.begin(), bananas.end());
	
	cout << maxBananas;

	return 0;
}