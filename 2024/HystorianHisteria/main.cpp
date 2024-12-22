#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	// part 1
	
	// int n = 1000;
	// vector<int> nums1(n), nums2(n);
	// unordered_map
	
	// for(int i = 0; i < n; ++i) {
	// 	cin >> nums1[i] >> nums2[i];
	// }
	
	// stable_sort(nums1.begin(), nums1.end());
	// stable_sort(nums2.begin(), nums2.end());
	
	// int distance = 0;
	// for(int i = 0; i < n; ++i) {
	// 	distance += abs(nums1[i] - nums2[i]);
	// }
	
	// cout << distance;
	
	// part 2
	
	int n = 1000, l, r;
	unordered_map<int,int> mpLeft , mpRight;
	for(int i = 0 ; i < n; ++i) {
		cin >> l >> r;
		mpLeft[l] += 1;
		mpRight[r] += 1;
	}

	long long similarity = 0;
	for(auto& pair: mpLeft) {
		similarity += (1ll * pair.first * pair.second * mpRight[pair.first]);
	}
	
	cout << similarity;

	return 0;
}