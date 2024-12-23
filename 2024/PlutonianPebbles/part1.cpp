#include <bits/stdc++.h>
using namespace std;

#define ll long long

void blink(vector<ll>& stones) {
	vector<ll> newStones;
	string stoneStr;
	for(int i = 0; i < stones.size(); ++i) {
		// 0 --> 1
		if(stones[i] == 0) {
			newStones.push_back(1);
			continue;
		}
		
		stoneStr = to_string(stones[i]);
		// Even digits
		if(stoneStr.length() % 2 == 0) {
			string s1 = stoneStr.substr(0,stoneStr.length() / 2);
			string s2 = stoneStr.substr(stoneStr.length() / 2);
			
			newStones.push_back(stoll(s1));
			newStones.push_back(stoll(s2));
			
			continue;
		}
		
		newStones.push_back(stones[i]*2024);
	}
	
	stones = newStones;
}

void print(vector<ll>& stones) {
	cout << "Total Stones: " << stones.size() << " ";
	for(auto& stone: stones) {
		cout << stone << " ";
	}
	cout << "\n";
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
	
	int blinks = 25;
	
	for(int i = 0; i < blinks; i++) {
		blink(stones);
	}
	
	cout << stones.size();

	return 0;
}