#include <bits/stdc++.h>
using namespace std;

long long quad[2][2];

int main(int argc, char const *argv[]) {
	int px, py, vx, vy;
	int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
	const int width = 101, height = 103;
	while(scanf(" p=%d,%d v=%d,%d", &px, &py, &vx, &vy) != EOF) {
		px = (((px + vx * 100) % width) + width) % width;
		py = (((py + vy * 100) % height) + height) % height;
		
		if(px != width/2 && py != height/2) {
			quad[px>width/2][py>height/2] += 1;
		}
	}
	
	long long safetyFactor = quad[0][0] * quad[0][1] * quad[1][0] * quad[1][1];
	
	cout << safetyFactor;

	return 0;
}