#include <bits/stdc++.h>
using namespace std;

#define ll long long

// up, right, bottom, left
vector<int> drow = {-1, 0, 1, 0};
vector<int> dcol = {0, 1, 0, -1};

bool inBounds(int row, int col, int rows, int cols) {
	return (row < rows && row >= 0 && col < cols && col >= 0);
}

bool goodNextCell(int row, int col, int dRow, int dCol, vector<vector<char>>& garden) {
	int rows = garden.size();
	int cols = garden[0].size();
	return (inBounds(row+dRow,col+dCol,rows,cols) && garden[row][col] == garden[row+dRow][col+dCol]);
}

void dfs(int row, int col, vector<vector<char>>& garden, vector<vector<bool>>& visited, int& area, int& vertices) {
	int rows = garden.size();
	int cols = garden[0].size();
	
	visited[row][col] = 1;
	area += 1;
	
	for(int dir = 0; dir < 4; dir++) {
		int nextDir = (dir+1)%4;
		
		//.  .
		// AA
		// AA 
		//.CB.
		if(!goodNextCell(row,col,drow[dir],dcol[dir],garden) && !goodNextCell(row,col,drow[nextDir],dcol[nextDir],garden)) {
			vertices += 1;
		}
		
		// 
		// A.
		// AA
		if(goodNextCell(row,col,drow[dir],dcol[dir],garden) && goodNextCell(row,col,drow[nextDir],dcol[nextDir],garden) && !goodNextCell(row,col,drow[dir]+drow[nextDir],dcol[dir]+dcol[nextDir],garden)) {
			vertices += 1;
		}
	}
	
	for(int dir = 0; dir < 4; dir++) {
		int nrow = row + drow[dir];
		int ncol = col + dcol[dir];
		if(goodNextCell(row,col,drow[dir],dcol[dir],garden) && !visited[nrow][ncol]) {
			dfs(nrow, ncol, garden, visited, area, vertices);
		}
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	int rows = 140; 
	int cols = 140;
	
	vector<vector<char>> garden(rows, vector<char>(cols));
	char ch;
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			cin >> ch;
			garden[r][c] = ch;
		}
	}
	
	vector<vector<bool>> visited(rows, vector<bool>(cols,0));
	
	int area, vertices;
	ll bulk_price = 0;
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			if(!visited[r][c]) {
				area = 0, vertices = 0;
				dfs(r,c,garden,visited,area,vertices);
				bulk_price += (area * vertices);
			}
		}
	}
	
	cout << bulk_price << "\n";

	return 0;
}