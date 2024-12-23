#include <bits/stdc++.h>
using namespace std;

void print(vector<int>& nums) {
	for(auto num: nums) {
		cout << num;
	}
	cout << "\n";
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);

	string denseDisk;
	cin >> denseDisk;
	
	int n = (int)denseDisk.length();
	vector<int> files, gapPos;
	for(int i = 0; i < n; ++i) {
		// 0-9
		int factor = denseDisk[i] - '0';
		while(factor--) {
			if(i % 2 == 0) {
				files.push_back(i/2);
			} else {
				gapPos.push_back(files.size());
				files.push_back(0);
			}
		}
	}
	
	reverse(gapPos.begin(), gapPos.end());
	
	for(int i = (int)files.size()-1; i >= 0; --i) {
		// it is file
		if(files[i]) {
			if(!gapPos.empty() && gapPos.back() < i) {
				files[gapPos.back()] = files[i];
				files[i] = 0;
				gapPos.pop_back();
			}
		}
	}
	
	long long checkSum = 0;
	for(int i = 0; i < (int)files.size(); ++i) {
		checkSum += files[i] * i;
	}
	
	cout << checkSum;

	return 0;
}