#include <bits/stdc++.h>
using namespace std;

const int T = 100000;
const int width = 101, height = 103;

vector<pair<int,int>> positions;
vector<pair<int,int>> velocities;
vector<string> grid(height, string(width,'.'));

void print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
	cout << "\n";
}

bool verticalSym(int threshold) {
	int cnt = 0;
	for(auto& pos: positions) {
		if(grid[width-1-pos.first][pos.second] == 'X') {
			if(++cnt >= threshold) return true;
		}
	}
	return false;
}

bool horizontalSym(int threshold) {
	int cnt = 0;
	for(auto& pos: positions) {
		if(grid[pos.first][height-1-pos.second] == 'X') {
			if(++cnt >= threshold) return true;
		}
	}
	return false;
}

void gridAfterTSecs(int time) {
	for(int i = 0; i < (int)positions.size(); ++i) {
		
		grid[positions[i].first][positions[i].second] = '.';
		
		positions[i].first += (time * velocities[i].first);
		positions[i].first = (positions[i].first % width + width) % width;
		
		positions[i].second += (time * velocities[i].second);
		positions[i].second = (positions[i].second % height + height) % height;
		
		grid[positions[i].first][positions[i].second] = 'X';
	}
}

int main(int argc, char const *argv[]) {
	int px, py, vx, vy;
	int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
	
	while(scanf(" p=%d,%d v=%d,%d", &px, &py, &vx, &vy) != EOF) {
		positions.push_back({px,py});
		velocities.push_back({vx,vy});
		grid[px][py] = 'X';
	}
	int time = 1;
	while(time < T) {
		gridAfterTSecs(1);
		if(verticalSym(100)) {
			cout << time << "\n";
			print(grid);
			break;
		}
		time++;
	}

	return 0;
}