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
				
				int steps;
				for(auto point: mp[ch]) {
					pr = point.first;
					pc = point.second;
					
					// drow is >= 0 always cause we are traversing row wise
					drow = r - pr;
					// dcol can be negative too
					dcol = c - pc;
					
					steps = 1;
					anr1 = pr - drow;
					anc1 = pc - dcol;
					
					// Check every equidistant antinode in the top/left of point
					while(anr1 >= 0 && anr1 < rows && anc1 >= 0 && anc1 < cols) {
						if(antiNodeGrid[anr1][anc1] != '#') {
							antinodes++;
							antiNodeGrid[anr1][anc1] = '#';
						}
						steps++;
						anr1 = pr - steps*drow;
						anc1 = pc - steps*dcol;
					}
					
					
					steps = 1;
					anr2 = r + drow;
					anc2 = c + dcol;
					
					// Check every equidistant antinode in the bottom/right of current
					while(anr2 >= 0 && anr2 < rows && anc2 >= 0 && anc2 < cols) {
						if(antiNodeGrid[anr2][anc2] != '#') {
							antinodes++;
							antiNodeGrid[anr2][anc2] = '#';
						}
						steps++;
						anr2 = r + steps*drow;
						anc2 = c + steps*dcol;
					}
				}
				
				grid[r][c] = ch;
				if(antiNodeGrid[r][c] != '#') {
					antinodes++;
					antiNodeGrid[r][c] = '#';
				}
				mp[ch].push_back({r,c});
			}
		}
	}
	
	print(antiNodeGrid);
	
	cout << antinodes << "\n";

	return 0;
}