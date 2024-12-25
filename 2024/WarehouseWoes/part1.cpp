#include <bits/stdc++.h>
using namespace std;

// Up, Right, Down, Left
vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
map<char,int> mp = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};

void print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
	cout << "\n";
}

bool pushBox(vector<string>& grid, int boxRow, int boxCol, int drow, int dcol) {
	int nrow = boxRow + drow;
	int ncol = boxCol + dcol;
	
	// There is an obstacle behind the box
	// Robot cannot push this box
	if(grid[nrow][ncol] == '#') {
		return false;
	}
	
	if(grid[nrow][ncol] == 'O') {
		// Try to push it
		if(pushBox(grid,nrow,ncol,drow,dcol)) {
			swap(grid[boxRow][boxCol],grid[nrow][ncol]);
			return true;
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
			if(grid[r][c] == 'O') {
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
		int pos = line.find('@');
		if(pos != string::npos) {
			row = grid.size();
			col = pos;
		}
		grid.push_back(line);
	}
	
	char move;
	pair<int,int> dir;
	int drow, dcol;
	int nrow, ncol;
	while(scanf(" %c", &move) != EOF) {
		dir = dirs[mp[move]];
		drow = dir.first, dcol = dir.second;
		
		// cout << move << "\n";
		
		nrow = row + drow;
		ncol = col + dcol;	
		
		// A Box in the Robot's path
		if(grid[nrow][ncol] == 'O') {
			// Try to push the box
			if(!pushBox(grid,nrow,ncol,drow,dcol)) {
				// print(grid);
				continue;
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