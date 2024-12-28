#include <bits/stdc++.h>
using namespace std;

#define Node pair<int, vector<int>>

// Up, Right, Down, Left
vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

int getLowestScore(int startRow, int startCol, int endRow, int endCol, int dirIdx, vector<string>& grid) {
		
	int rows = grid.size();
	int cols = grid[0].length();
	
	priority_queue<Node, vector<Node>, greater<Node>> pq;
	
	vector<vector<int>> dis(rows, vector<int>(cols,INT_MAX));
	
	for(int d = -1; d <= 1; d++) {
		int dir = ((dirIdx + d) % 4 + 4) % 4;
		int penalty = 0;
		if(d != 0) {
			penalty = 1000;
		}
		pq.push({penalty,vector<int>{dir,startRow,startCol}});
	}
	
	while(!pq.empty()) {
		auto node = pq.top(); pq.pop();
		int cost = node.first;
	
		auto vec = node.second;
		int ndir = vec[0];
		int row = vec[1];
		int col = vec[2];
		
		// printf("R: %d C: %d Dir: %d Cost:%d\n",row,col,ndir,cost);
		
		if(row == endRow && col == endCol) {
			break;
		}
		
		for(int d = -1; d <= 1; d++) {
			int newdir = ((ndir + d) % 4 + 4) % 4;
			
			int nrow = row + dirs[newdir].first;
			int ncol = col + dirs[newdir].second;
			
			if(grid[nrow][ncol] == '#') continue;
			
			int penalty = 0;
			if(d != 0) {
				penalty = 1000;
			}
			
			int newCost = cost + 1 + penalty;
			
			if(newCost >= dis[nrow][ncol]) continue;
			
			dis[nrow][ncol] = newCost;
			pq.push({newCost,vector<int>{newdir,nrow,ncol}});
			
			// printf("NDir %d NCost: %d ", newdir, newCost);
		}
		
		// printf("\n");
	}
	
	// int width = 5;
	// for(int r = 0; r < rows; ++r) {
	// 	for(int c = 0; c < cols; ++c) {
	// 		if(dis[r][c] == INT_MAX) dis[r][c] = -1;
	// 		printf("%-*s|", width, to_string(dis[r][c]).c_str());
	// 	}
	// 	printf("\n");
	// }
	
	return dis[endRow][endCol];
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
		}
		
		pos = line.find('S');
		if(pos != string::npos) {
			startRow = grid.size();
			startCol = pos;
		}
		
		grid.push_back(line);
	}
	
	// cout << startRow << " " << startCol << "\n";
	// cout << endRow << " " << endCol << "\n";
	
	// Right
	int dir = 1;
	int score = getLowestScore(startRow,startCol,endRow,endCol,dir,grid);
	
	cout << score;

	return 0;
}