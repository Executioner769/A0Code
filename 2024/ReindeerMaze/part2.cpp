#include <bits/stdc++.h>
using namespace std;

// {distance, {row, col, direction}}
#define Node pair<int, vector<int>>

// Up, Right, Down, Left
vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
}

// cell {r,c};
set<vector<int>> seen;
// cell {r,c,d};
set<vector<int>> gone;
void tracePath(int r, int c, int d, vector<string>& grid, map<vector<int>,vector<vector<int>>>& prev) {
	if(gone.find({r,c,d}) != gone.end()) {
		return;
	}
	
	gone.insert({r,c,d});
	seen.insert({r,c});
	
	grid[r][c] = 'O';
	
	for(auto vec: prev[{r,c,d}]) {
		tracePath(vec[0], vec[1], vec[2], grid, prev);
	}
	
}

vector<int> getShortestPaths(int startRow, int startCol, int endRow, int endCol, int dir, vector<string>& grid) {
	
	priority_queue<Node, vector<Node>, greater<Node>> pq;
	
	pq.push({0,{startRow, startCol, dir}});
	
	int rows = grid.size();
	int cols = grid[0].length();
	
	// {[row][col][dir]} ==> list of previous cells that help me reach here
	map<vector<int>, vector<vector<int>>> prev;
	
	vector<vector<vector<int>>> dis(rows, vector<vector<int>>(cols, vector<int>(4, INT_MAX)));
	
	int distance = 0;
	
	while(!pq.empty()) {
		auto node = pq.top(); pq.pop();
		
		int cost = node.first;
		
		auto vec = node.second;
		int row = vec[0];
		int col = vec[1];
		int ndir = vec[2];
		
		if(dis[row][col][ndir] < cost) {
			continue;
		}
		
		if(row == endRow && col == endCol) {
			distance = cost;
			tracePath(row,col,ndir,grid,prev);
			break;
		}
		
		int dr = dirs[ndir].first;
		int dc = dirs[ndir].second;
		
		int nrow = row + dr;
		int ncol = col + dc;
		
		if(grid[nrow][ncol] == '.') {
			int newCost = cost + 1;
			
			if(dis[nrow][ncol][ndir] > newCost) {
				dis[nrow][ncol][ndir] = newCost;
				pq.push({newCost, {nrow, ncol, ndir}});
				
				prev[{nrow,ncol,ndir}].push_back({row,col,ndir});
			} else if(dis[nrow][ncol][ndir] == newCost) {
				prev[{nrow,ncol,ndir}].push_back({row,col,ndir});
			}
		}
		
		vector<int> turns = {-1,1};
		for(int turn: turns) {
			int newDir = ((ndir + turn) % 4 + 4) % 4;
			int newCost = cost + 1000;
			
			if(dis[row][col][newDir] > newCost) {
				dis[row][col][newDir] = newCost;
				pq.push({newCost, {row, col, newDir}});
				
				prev[{row,col,newDir}].push_back({row,col,ndir});
			} else if(dis[row][col][newDir] == newCost) {
				prev[{row,col,newDir}].push_back({row,col,ndir});
			}
		}
	}
	
	int tiles = seen.size();
	return vector<int>{distance,tiles};
}

int main(int argc, char const *argv[]) {
	
	vector<string> grid;
	
	int endRow, endCol;
	int startRow, startCol;
	int pos;
	
	for(string line; getline(cin,line);) {
		pos = line.find('E');
		if(pos != string::npos) {
			endRow = grid.size();
			endCol = pos;
			
			line[pos] = '.';
		}
		
		pos = line.find('S');
		if(pos != string::npos) {
			startRow = grid.size();
			startCol = pos;
			
			line[pos] = '.';
		}
		
		grid.push_back(line);
	}
	
	int dir = 1;
	auto res = getShortestPaths(startRow, startCol, endRow, endCol, dir, grid);
	
	print(grid);
	cout << res[0] << " " << res[1] << "\n";
	
	return 0;
}