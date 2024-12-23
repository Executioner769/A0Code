#include <bits/stdc++.h>
#include <chrono>
using namespace std;


// up, right, down, left
vector<int> drow = {-1, 0, 1, 0};
vector<int> dcol = {0, 1, 0, -1};

int dfs(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& visited) {
	visited[row][col] = 1;
	
	int rows = grid.size();
	int cols = grid[0].size();
	
	// Reached the Highest point
	if(grid[row][col] == 9) {
		return 1;
	}
	
	int trailheads = 0;
	for(int dir = 0; dir < 4; ++dir) {
		int nrow = row + drow[dir];
		int ncol = col + dcol[dir];
		
		//in bounds
		if(nrow < rows && nrow >= 0 && ncol < cols && ncol >= 0) {
			// if not visited
			if(!visited[nrow][ncol]) {
				// if next = current + 1
				if(grid[nrow][ncol] == grid[row][col] + 1) {
					trailheads += dfs(nrow, ncol, grid, visited);
				}
			}
		}
	}
	
	return trailheads;
}

int getTrailHeads(pair<int,int> start, vector<vector<int>>& grid) {
	int rows = grid.size();
	int cols = grid[0].size();
	vector<vector<int>> visited(rows, vector<int>(cols,0));
	int row = start.first;
	int col = start.second;
	return dfs(row, col, grid, visited);
}

void print(vector<vector<int>>& grid) {
	int rows = grid.size();
	int cols = grid[0].size();
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cout << grid[r][c] << " ";
		}
		cout << "\n";
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	auto start = chrono::high_resolution_clock::now();
	
	int rows = 48, cols = 48;
	
	vector<vector<int>> grid(rows,vector<int>(cols));
	
	vector<pair<int,int>> startPoints;
	
	// Read the Input and Track all the trail head cells
	char ch;
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cin >> ch;
			grid[r][c] = ch - '0';
			if(grid[r][c] == 0) {
				startPoints.push_back({r,c});
			}
		}
	}
	
	int totalTrailHeads = 0;
	int trailheads = 0;
	
	for(auto start: startPoints) {
		trailheads = getTrailHeads(start,grid);
		// cout << trailheads << " ";
		totalTrailHeads += trailheads;
	}
	// cout << "\n";
	
	cout << totalTrailHeads << "\n";
	
	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	// cout << duration.count() << "\n";
	
	return 0;
}