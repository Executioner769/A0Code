#include <bits/stdc++.h>
using namespace std;


bool isSafe(vector<int>& level) {
	int diff = 0;
	bool isIncreasing = false;
	bool isDecreasing = false;
	
	for(int i = 1; i < level.size(); ++i) {
		diff = level[i-1] - level[i];
		if(abs(diff) > 3 || abs(diff) < 1) {
			return false;
		}
		
		if(diff > 0) {
			isDecreasing = true;
		} else {
			isIncreasing = true;
		}
	}
	return isIncreasing ^ isDecreasing;
}

vector<int> split(string str) {
	istringstream iss(str);
	string strNum;
	vector<int> nums;
	
	while(iss >> strNum) {
		nums.push_back(stoi(strNum));
	}
	return nums;
}

int main(int argc, char const *argv[]) {
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	

	int reports = 1000, levels = 5;
	vector<int> level(levels);
	
	int safeLevels = 0, counter = 1;
	
	for(string line; getline(cin, line); counter += 1) {
		vector<int> level = split(line);
		if(isSafe(level)) {
			safeLevels += 1;
		} else {
			int num = 0;
			for(int i = 0; i < level.size(); ++i) {
				num = level[i];
				level.erase(level.begin() + i);
				if(isSafe(level)) {
					safeLevels += 1;
					level.insert(level.begin() + i, num);
					break;
				}
				level.insert(level.begin() + i, num);
			}
		}
	}	
	
	cout << safeLevels;

	return 0;
}