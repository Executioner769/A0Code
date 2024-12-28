#include <bits/stdc++.h>
using namespace std;

void generateShortestPathMap(vector<string>& grid, map<pair<char,char>,string>& mp, vector<vector<int>>& dirs, vector<char>& dMap) {
	int R = grid.size();
	int C = grid[0].length();

	for(int r = 0; r < R; ++r) {
		for(int c = 0; c < C; ++c) {
			
			queue<pair<string,vector<int>>> q;
			q.push({"", {r,c}});
			
			vector<vector<int>> visited(R, vector<int>(C,0));
			
			visited[r][c] = 1;
			
			while(!q.empty()) {
				auto node = q.front(); q.pop();
				string path = node.first;
				
				int row = node.second[0];
				int col = node.second[1];
				
				path.push_back('A');
				mp[{grid[r][c], grid[row][col]}] = path;
				path.pop_back();
				
				for(int d = 0; d < 4; ++d) {
					auto dir = dirs[d];
					int nrow = row + dir[0];
					int ncol = col + dir[1];
					
					// In bounds
					if(nrow < R && ncol < C && nrow >= 0 && ncol >= 0) {
						
						if(!visited[nrow][ncol] && grid[nrow][ncol] != '#') {
							visited[nrow][ncol] = 1;
							path.push_back(dMap[d]);
							q.push({path,{nrow,ncol}});
							path.pop_back();
						}
						
					}
				}
			}
						
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
	
	vector<string> dialpad = {
		"789",
		"456",
		"123",
		"#0A"
	};
	
	vector<string> movepad = {
		"#^A",
		"<v>"
	};
	
	vector<vector<int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
	vector<char> dMap = {'^', '>', 'v', '<'};
	
	map<pair<char,char>,string> dialpadMap;
	generateShortestPathMap(dialpad, dialpadMap, dirs, dMap);
	
	dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};
	dMap = {'v', '>', '^', '<'};
	
	map<pair<char,char>,string> movepadMap;
	generateShortestPathMap(movepad, movepadMap, dirs, dMap);
	
	string code;
	char from = 'A';
	
	int totalComplexity = 0; 
	while(getline(cin,code)) {

		int totalLen = 0;
		
		
		int codeNum = 0;
		for(auto to: code) {
			
			// printf("%c --> %c: ",from, to);
			
			string temp1, temp2;
			if(isdigit(to)) {
				codeNum = codeNum * 10 + to - '0';
			}
			
			temp1 = dialpadMap[{from,to}];

			int len1 = 0;
			char from1 = 'A';
			for(auto to1: temp1) {
				
				string r2code1, r2code2;
				int r2len1 = 0;
				
				r2code1 = movepadMap[{from1,to1}];
				
				char from3 = 'A';
				for(auto to3: r2code1) {
					r2len1 += movepadMap[{from3,to3}].length();
					from3 = to3;
				}
				
				r2code2 = r2code1;
				r2code2.pop_back();
				reverse(r2code2.begin(), r2code2.end());
				r2code2.push_back('A');
				
				int r2len2 = 0;
				from3 = 'A';
				for(auto to3: r2code2) {
					r2len2 += movepadMap[{from3,to3}].length();
					from3 = to3;
				}
				
				if(r2len1 > r2len2) {
					swap(r2len1, r2len2);
				}
				
				len1 += r2len1;
				
				from1 = to1;
			}
			
			// printf(" T1: %s %d", temp1.c_str(), len1);
			
			temp2 = temp1;
			temp2.pop_back();
			reverse(temp2.begin(), temp2.end());
			temp2.push_back('A');
			
			int len2 = 0;
			from1 = 'A';
			for(auto to1: temp2) {
				string r2code1, r2code2;
				int r2len1 = 0;
				
				r2code1 = movepadMap[{from1,to1}];
				
				char from3 = 'A';
				for(auto to3: r2code1) {
					r2len1 += movepadMap[{from3,to3}].length();
					from3 = to3;
				}
				
				r2code2 = r2code1;
				r2code2.pop_back();
				reverse(r2code2.begin(), r2code2.end());
				r2code2.push_back('A');
				
				int r2len2 = 0;
				from3 = 'A';
				for(auto to3: r2code2) {
					r2len2 += movepadMap[{from3,to3}].length();
					from3 = to3;
				}
				
				if(r2len1 > r2len2) {
					swap(r2len1, r2len2);
				}
				
				len2 += r2len1;
				
				from1 = to1;
			}
			
			// printf(" T2: %s %d\n", temp2.c_str(), len2);
			
			if(len1 > len2) {
				swap(len1,len2);
			}
			
			totalLen += len1;

			from = to;
		}
		
		printf("%s %d %d\n", code.c_str(), codeNum, totalLen);
	}

	return 0;
}