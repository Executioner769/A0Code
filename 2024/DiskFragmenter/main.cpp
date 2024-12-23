#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	   
	char ch;
	vector<int> disk;
	int idx = 0;
	
	while ((ch = getchar()) != '\n') {
		int num = ch - '0';
		if(idx % 2 == 0) {
			while(num--) {
				disk.push_back(idx/2);
			}
		} else {
			while(num--) {
				disk.push_back(-1);
			}
		}
		idx += 1;
	}
	
	int left = 0;
	int right = disk.size() - 1;
	
	while(left < right && (left < disk.size() && right >= 0)) {
		while(disk[left] != -1) left++;
		while(disk[right] == -1) right--;
		
		// out of bounds
		if(!(left < disk.size() && right >= 0)) break;
		
		if(disk[left] == -1 && disk[right] != -1)
			swap(disk[left],disk[right]);
	}
	
	// Handle this case
	// -1 num -1 
	if(left-1 >= 0 && disk[left] != -1 && disk[left-1] == -1) {
		swap(disk[left-1],disk[left]);
	}
	
	ll checkSum = 0;
	for(int idx = 0; idx < disk.size(); idx++) {
		if(disk[idx] == -1) break;
		checkSum += 1ll * idx * disk[idx];
	}
	
	cout << checkSum << "\n";

	return 0;
}