#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};

void print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
	cout << "\n";
}

bool bfs(vector<string>& grid) {
	int sr = 0, sc = 0;
	int er = 70, ec = 70;
	
	int shortestDistance = 0;
	
	int R = grid.size();
	int C = grid[0].length();
	
	vector<vector<int>> seen(R, vector<int>(C,0));
	
	queue<vector<int>> q;
	q.push({0,sr,sc});
	
	while(!q.empty()) {
		auto vec = q.front(); q.pop();
		int cost = vec[0];
		int row = vec[1];
		int col = vec[2];
		
		if(row == er && col == ec) {
			break;
		}
		
		for(auto& dir: dirs) {
			int nrow = row + dir[0];
			int ncol = col + dir[1];
			
			if(nrow >= 0 && nrow < R && ncol >= 0 && ncol < C) {
				if(!seen[nrow][ncol] && grid[nrow][ncol] == '.') {
					seen[nrow][ncol] = 1;
					q.push({cost + 1,nrow,ncol});
				}
			}
		}
	}
	
	return seen[er][ec];
}

int main(int argc, char const *argv[]) {
	
	int R = 71, C = 71;
	vector<string> grid(R, string(C,'.'));
	
	vector<int> rows, cols;
	int r,c;
	while(scanf(" %d,%d",&r,&c) != EOF) {
		rows.push_back(r);
		cols.push_back(c);
	}
	
	int bytes = rows.size();
	int byte;
	for(byte = 0; byte < bytes; ++byte) {
		grid[rows[byte]][cols[byte]] = '#';
		if(!bfs(grid)) {
			printf("%d,%d", rows[byte],cols[byte]);
			break;
		}
	}
	
	return 0;
}