#include <bits/stdc++.h>
using namespace std;


void print(vector<vector<char>>& grid) {
	int rows = grid.size(), cols = grid[0].size();
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cout << grid[r][c];
		}
		cout << "\n";
	}
}

void print(int row, int col, string label) {
	cout << label << ": " << "{" << row << "," << col << "}\n";
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	int rows = 50, cols = 50;
	vector<vector<char>> grid(rows, vector<char>(cols,'.'));
	vector<vector<char>> antiNodeGrid(rows, vector<char>(cols,'.'));
	
	unordered_map<char, vector<pair<int,int>> > mp; 
	
	int antinodes = 0;
	
	char ch;
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cin >> ch;
			if(ch != '.') {
				// Add antinodes for all the previously present antennas of the same frequency
				
				// previous antenna cords
				int pr,pc;
				
				// delta between previous antenna and current antenna
				int drow,dcol;
				
				// the cords of the antinodes
				// antinode1 is on the top/left, antinode2 is on the bottom/right
				int anr1, anr2, anc1, anc2;
				for(auto point: mp[ch]) {
					pr = point.first;
					pc = point.second;
					
					// drow is >= 0 always cause we are traversing row wise
					drow = r - pr;
					// dcol can be negative too
					dcol = c - pc;
					
					anr1 = pr - drow;
					anr2 = r + drow;
					
					
					// #...
					// .0..
					// ..0.
					// ...#
					// dcol is positive
					
					// ...#
					// ..0.
					// .0..
					// #...
					// dcol is negative
					
					anc1 = pc - dcol;
					anc2 = c + dcol;
					
					// antinode1 in bounds
					if(anr1 >= 0 && anr1 < rows && anc1 >= 0 && anc1 < cols) {
						if(antiNodeGrid[anr1][anc1] != '#') {
							antinodes++;
							antiNodeGrid[anr1][anc1] = '#';
						}
					}
					
					// antinode2 in bounds
					if(anr2 >= 0 && anr2 < rows && anc2 >= 0 && anc2 < cols) {
						if(antiNodeGrid[anr2][anc2] != '#') {
							antinodes++;
							antiNodeGrid[anr2][anc2] = '#';
						}
					}
				}
				
				grid[r][c] = ch;
				antiNodeGrid[r][c] = ch;
				mp[ch].push_back({r,c});
			}
		}
	}
	
	print(antiNodeGrid);
	
	cout << antinodes << "\n";

	return 0;
}