#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	 
	int answer = 0;
	char word[128];
	// Solving system of linear equations with 2 variables
	// a1x + b1y = c1
	// a2x + b2y = c2
	
	int a1, a2, b1, b2, c1, c2;
	while(scanf("%s", word) != EOF) {
		scanf("%s", word);
		scanf(" X+%d, ", &a1);
		scanf(" Y+%d", &a2);
		
		scanf("%s", word);
		scanf("%s", word);
		scanf(" X+%d, ", &b1);
		scanf(" Y+%d", &b2);
		
		scanf("%s", word);
		scanf(" X=%d, ", &c1);
		scanf(" Y=%d", &c2);
		
		int det = a1*b2 - a2*b1;
		int x = (b2*c1 - b1*c2) / det;
		int y = (a1*c2 - a2*c1) / det;
		
		if((a1*x + b1*y == c1) && (a2*x + b2*y == c2)) {
			answer += 3*x + y;
		}
	}
	
	cout << answer;

	return 0;
}