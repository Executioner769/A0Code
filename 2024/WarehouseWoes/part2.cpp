#include <bits/stdc++.h>
using namespace std;

// Up, Right, Down, Left
vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
map<char,int> mp = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};

void print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
}

bool pushBoxesUD(vector<string>& grid, set<pair<int,int>>& boxes, int drow, int dcol) {
	bool ableToPush = true;
	set<pair<int,int>> nextBoxes;
	
	for(auto &box: boxes) {
		int nrow = box.first + drow;
		int ncol = box.second + dcol;
		
		if(grid[nrow][ncol] == '#') {
			ableToPush = false;
			break;
		}
		
		if(grid[nrow][ncol] == '[' || grid[nrow][ncol] == ']') {
			if(grid[nrow][ncol] == '[') {
				nextBoxes.insert({nrow,ncol});
				nextBoxes.insert({nrow,ncol+1});
			}
			
			if(grid[nrow][ncol] == ']') {
				nextBoxes.insert({nrow,ncol-1});
				nextBoxes.insert({nrow,ncol});
			}
		}
	}
	
	if(!ableToPush) {
		return false;
	}
	
	if(ableToPush && nextBoxes.size() != 0) {
		if(!pushBoxesUD(grid,nextBoxes,drow,dcol)) {
			return false;
		}
	}
	
	if(ableToPush) {
		for(auto &box: boxes) {
			int nrow = box.first + drow;
			int ncol = box.second + dcol;
			
			swap(grid[box.first][box.second], grid[nrow][ncol]);
		}
		
		return true;
	}
	
	return false;
	
}

bool pushBoxLR(vector<string>& grid, int boxRow, int boxCol, int drow, int dcol) {
	int nrow = boxRow + drow;
	int ncol = boxCol + dcol;
	
	// There is an obstacle behind the box
	// Robot cannot push this box
	if(grid[nrow][ncol] == '#') {
		return false;
	}
	
	if(grid[nrow][ncol] == '[' || grid[nrow][ncol] == ']') {
		// Try to push it
		if(!pushBoxLR(grid,nrow,ncol,drow,dcol)) {
			return false;
		}
	}
	
	// Push the box
	if(grid[nrow][ncol] == '.') {
		swap(grid[boxRow][boxCol],grid[nrow][ncol]);
		return true;
	}
	
	return false;
}

int getGPSum(vector<string>& grid) {
	int sum = 0;
	for(int r = 0; r < grid.size(); ++r) {
		for(int c = 0; c < grid[r].length(); ++c) {
			if(grid[r][c] == '[') {
				sum += 100*r + c;
			}
		}
	}
	return sum;
}

int main(int argc, char const *argv[]) {
	
	vector<string> grid;
	int row, col;
	for(string line;getline(cin,line);) {
		if(line.size() == 0) break;
		string str;
		for(auto& ch: line) {
			if(ch == '@') {
				row = grid.size();
				col = str.length();
				
				str += "@.";
			} else if(ch == 'O') {
				str += "[]";
			} else {
				str += string(2,ch);
			}
		}
		grid.push_back(str);
	}
	
	
	char move;
	pair<int,int> dir;
	int drow, dcol;
	int nrow, ncol;
	while(scanf(" %c", &move) != EOF) {
		dir = dirs[mp[move]];
		drow = dir.first, dcol = dir.second;
		
		// print(grid);
		// cout << move << "\n";
		
		nrow = row + drow;
		ncol = col + dcol;	
		
		// A Box in the Robot's path
		if(grid[nrow][ncol] == '[' || grid[nrow][ncol] == ']') {
			// Try to push the box
			// if the dir is left/right
			if(mp[move] % 2 == 1) {
				if(!pushBoxLR(grid,nrow,ncol,drow,dcol)) {
					// print(grid);
					continue;
				}
			} else {
				// if the dir is up/down
				set<pair<int,int>> boxes;
				if(grid[nrow][ncol] == '[') {
					boxes.insert({nrow,ncol});
					boxes.insert({nrow,ncol+1});
				}
				
				if(grid[nrow][ncol] == ']') {
					boxes.insert({nrow,ncol-1});
					boxes.insert({nrow,ncol});
				}
				
				if(!pushBoxesUD(grid,boxes,drow,dcol)) {
					// print(grid);
					continue;
				}
			}
		}
		
		// No obstacle in the given diection. So the robot moves to new position
		if(grid[nrow][ncol] == '.') {
			// move the robot
			swap(grid[nrow][ncol],grid[row][col]);
			
			// update the new pos of the robot
			row = nrow;
			col = ncol;
			
			// print(grid);
		}
		
		// Wall in the given diection. So the robot doesn't move
		if(grid[nrow][ncol] == '#') {
			// print(grid);
			continue;
		}
	}
	
	print(grid);
	
	int gpsSum = getGPSum(grid);
	
	cout << gpsSum << "\n";
	
	return 0;
}