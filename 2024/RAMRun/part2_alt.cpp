#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
private:
	vector<int> parent, size;
public:
	DisjointSet(int N) {
		parent.resize(N+1);
		for (int i = 0; i < N+1; ++i) {
			parent[i] = i;
		}
		
		size.resize(N+1,1);
	}
	
	int findParent(int node) {
		if(parent[node] == node) return node;
		else return parent[node] = findParent(parent[node]);
	}
	
	bool unionBySize(int n1, int n2) {
		int ult_pn1 = findParent(n1);
		int ult_pn2 = findParent(n2);
		
		if(ult_pn1 == ult_pn2) return false;
		if(size[ult_pn1] < size[ult_pn2]) swap(ult_pn1,ult_pn2);
		if(size[ult_pn1] >= size[ult_pn2]) {
			parent[ult_pn2] = ult_pn1;
			size[ult_pn1] += size[ult_pn2];
		}
		return true;
	}
	
};

void print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
	cout << "\n";
}

int main(int argc, char const *argv[]) {
	
	int R = 71, C = 71;
	vector<string> grid(R, string(C,'.'));
	
	vector<int> rows, cols;
	int r,c;
	while(scanf(" %d,%d",&r,&c) != EOF) {
		rows.push_back(r);
		cols.push_back(c);
		
		grid[r][c] = '#';
	}
	
	int cells = R * C;
	DisjointSet ds(cells);
	
	vector<vector<int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
	
	for(r = 0; r < R; ++r) {
		for(c = 0; c < C; ++c) {
			if(grid[r][c] == '.') {
				for(auto& dir: dirs) {
					int nr = r + dir[0];
					int nc = c + dir[1];
					
					if(nr < R && nr >= 0 && nc < C && nc >=0) {
						if(grid[nr][nc] == '.') {
							int cell1 = r*R + c;
							int cell2 = nr*R + nc;
							
							ds.unionBySize(cell1, cell2);
						}
					}
				}
			}
		}
	}
	
	int byte;
	int bytes = rows.size();
	
	int startCell = 0;
	int endCell = cells-1;
	
	for(byte = bytes-1; byte >= 0; --byte) {
		r = rows[byte];
		c = cols[byte];
		
		grid[r][c] = '.';
		
		for(auto& dir: dirs) {
			int nr = r + dir[0];
			int nc = c + dir[1];
			
			if(nr < R && nr >= 0 && nc < C && nc >=0) {
				if(grid[nr][nc] == '.') {
					int cell1 = r*R + c;
					int cell2 = nr*R + nc;
					
					ds.unionBySize(cell1, cell2);
				}
			}
		}
		
		if(ds.findParent(startCell) == ds.findParent(endCell)) {
			printf("%d,%d", rows[byte],cols[byte]);
			break;
		}
	}
	
	return 0;
}