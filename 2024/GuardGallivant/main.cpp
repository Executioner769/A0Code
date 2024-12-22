#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};

// Assuming the guard never stucks in a loop
void patrol(pair<int,int> guard, int dir,vector<vector<char>>& grid, vector<vector<bool>>& visited, int& cells) {
	int rows = grid.size(), cols = grid[0].size();
	while(true) {
		if(!visited[guard.first][guard.second]) {
			visited[guard.first][guard.second] = true;
			cells += 1;
		}
		
		int nr = guard.first + directions[dir].first;
		int nc = guard.second + directions[dir].second;
		
		if(!(nr < rows && nc < cols && nr >= 0 && nc >= 0)) {
			// Guard has stepped out of the grid
			return;
		}
		
		if(grid[nr][nc] == '.') {
			guard = make_pair(nr,nc);
		} else {
			dir = (dir + 1) % 4;
		}
	}
}

// Check if the guard stucks in a loop
// [Finished in 5.7s]

// With visited optimization
// [Finished in 1.8s] 
bool checkPatrolCycleMatrix(pair<int,int> guard, int dir, vector<vector<char>>& grid) {
	int rows = grid.size(), cols = grid[0].size();
	int row, col;
	vector<vector<vector<bool>>> vis(4, vector<vector<bool>>(rows, vector<bool>(cols,false)));
	while(true) {
		row = guard.first;
		col = guard.second;
		
		// the guard has reached a cell with same direction second time
		// Cycle
		if(vis[dir][row][col]) {
			return true;
		}
		
		vis[dir][row][col] = true;

		int nr = row + directions[dir].first;
		int nc = col + directions[dir].second;
		
		if(!(nr < rows && nc < cols && nr >= 0 && nc >= 0)) {
			// Guard has stepped out of the grid
			// No Cycle
			return false;
		}
		
		if(grid[nr][nc] == '.') {
			guard = make_pair(nr,nc);
		} else {
			dir = (dir + 1) % 4;
		}
	}
}

// Check if the guard stucks in a loop
// [Finished in 3.2s]

// With visited optimization
// [Finished in 1.0s]
bool checkPatrolCycleHash(pair<int,int> guard, int dir, vector<vector<char>>& grid) {
	int rows = grid.size(), cols = grid[0].size();
	int row, col;
	vector<bool> vis(rows * cols * 4);
	while(true) {
		row = guard.first;
		col = guard.second;
		
		int hash = (((row * cols) + col) * 4) + dir; 
		// the guard has reached a cell with same direction second time
		// Cycle
		if(vis[hash]) {
			return true;
		}
		
		vis[hash] = true;

		int nr = row + directions[dir].first;
		int nc = col + directions[dir].second;
		
		if(!(nr < rows && nc < cols && nr >= 0 && nc >= 0)) {
			// Guard has stepped out of the grid
			// No Cycle
			return false;
		}
		
		if(grid[nr][nc] == '.') {
			guard = make_pair(nr,nc);
		} else {
			dir = (dir + 1) % 4;
		}
	}
}

// Check if the guard stucks in a loop
// [Finished in 1.5s]

// With visited optimization
// [Finished in 1.1s]
bool checkPatrolCycleMoves(pair<int,int> guard, int dir, vector<vector<char>>& grid) {
	int rows = grid.size(), cols = grid[0].size();
	int moves = 0, maxMoves = rows * cols * 4;
	int row = guard.first, col = guard.second;
	while(true) {
		moves++;
		// the guard has crossed max possible moves 
		// Cycle
		if(moves == maxMoves) {
			return true;
		}

		int nrow = row + directions[dir].first;
		int ncol = col + directions[dir].second;
		
		if(!(nrow < rows && ncol < cols && nrow >= 0 && ncol >= 0)) {
			// Guard has stepped out of the grid
			// No Cycle
			return false;
		}
		
		if(grid[nrow][ncol] == '.') {
			row = nrow;
			col = ncol;
		} else {
			dir = (dir + 1) % 4;
		}
	}
}

void print(vector<vector<char>>& grid) {
	int rows = grid.size(), cols = grid[0].size();
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cout << grid[r][c];
		}
		cout << "\n";
	}
	cout << "\n";
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	int rows = 130, cols = 130;
	vector<vector<char>> grid(rows ,vector<char>(cols,'.'));
	char ch;
	int dir = 0;
	pair<int,int> guard;
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cin >> ch;
			if(ch == '#') grid[r][c] = ch;
			if(ch == '^' ) {
				guard = make_pair(r,c);
			}
		}
	}
	
	vector<vector<bool>> visited(rows, vector<bool>(cols,false));
	int visitedPositions = 0;
	
	patrol(guard,dir,grid,visited,visitedPositions);
	
	cout << visitedPositions << "\n";
	
	int obstacleCount = 0;
	
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			// not the start pos and it is empty pos i.e '.'
			// optimization try placing obstacle on the pevious visited patrol path
			if(guard != make_pair(r,c) && grid[r][c] == '.' && visited[r][c]) {
				grid[r][c] = '0';
				if(checkPatrolCycleHash(guard, dir, grid)) {
					obstacleCount += 1;
				}
				grid[r][c] = '.';
			}
		}
	} 
	
	cout << obstacleCount << "\n";
	
	return 0;
}