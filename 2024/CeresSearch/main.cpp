#include <bits/stdc++.h>
using namespace std;

void print(vector<vector<char>>& grid) {
	int rows = grid.size() ,cols = grid[0].size();
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			cout << grid[r][c] << " ";
		}
		cout << "\n";
	}
}

int check(int r, int c, int dir, vector<vector<char>>& grid) {
	int rows = grid.size() ,cols = grid[0].size();

	int xmasCount = 0;
	
	int drow[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dcol[] = {0, 1, 1, 1, 0, -1, -1, -1};
	
	for(int i = 1; i <= 3; ++i) {
		int nr = r + drow[dir];
		int nc = c + dcol[dir];
		
		if((nr < rows && nr >= 0 && nc < cols && nc >= 0)) {
			if(grid[r][c] == 'X' && grid[nr][nc] == 'M') {
				r = nr; c = nc;
			} else if(grid[r][c] == 'M' && grid[nr][nc] == 'A') {
				r = nr; c = nc;
			} else if(grid[r][c] == 'A' && grid[nr][nc] == 'S') {
				xmasCount += 1;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	
	return xmasCount;
}

bool check(int r, int c, vector<vector<char>>& grid) {
	int rows = grid.size() ,cols = grid[0].size();
	int masCount = 0;
	
	// topRight, bottomLeft, topLeft, bottomRight
	int drow[] = {-1, 1, -1, 1};
	int dcol[] = {1, -1, -1, 1};
	
	char chars[] = {'.', '.', '.', '.'};
	for(int i = 0; i < 4; i++) {
		int nr = r + drow[i];
		int nc = c + dcol[i];
		if((nr < rows && nr >= 0 && nc < cols && nc >= 0)) {
			chars[i] = grid[nr][nc];
		}
	}
	
	char topRight = chars[0], bottomLeft = chars[1], topLeft = chars[2], bottomRight = chars[3];
	
	// M . .  S . .
	// . A .  . A .
	// . . S  . . M
	if((topLeft == 'M' && bottomRight == 'S') || (topLeft == 'S' && bottomRight == 'M')) {
		masCount += 1;
	}
	
	// . . M  . . S
	// . A .  . A .
	// S . .  M . .	
	if((topRight == 'M' && bottomLeft == 'S') || (topRight == 'S' && bottomLeft == 'M')) {
		masCount += 1;
	}
	
	return masCount == 2;
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	int xmasCount = 0;
	
	int rows = 140, cols = 140;
	vector<vector<char>> grid(rows, vector<char>(cols));
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			cin >> grid[r][c];
		}
	}
	
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			
			// Part: 1
			// if(grid[r][c] == 'X') {
			// 	for(int dir = 0; dir < 8; ++dir) {
			// 		xmasCount = check(r,c,dir,grid);
			// 		total += xmasCount;
			// 	}
			// }
			
			//Part: 2
			if(grid[r][c] == 'A') {
				if(check(r,c,grid)) xmasCount+= 1;
			}
		}
	}
	
	cout << xmasCount;
	
	return 0;
}