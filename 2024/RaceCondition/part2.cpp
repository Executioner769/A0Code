#include <bits/stdc++.h>
using namespace std;

print(vector<string>& grid) {
	for(auto& str: grid) {
		cout << str << "\n";
	}
	cout << "\n";
}

print(vector<vector<int>>& nums) {
	int R = nums.size();
	int C = nums[0].size();
	
	for(int r = 0; r < R; ++r) {
		for(int c = 0; c < C; ++c) {
			printf("%3d", nums[r][c]);
		}
		cout << "\n";
	}
	cout << "\n";
}

int main(int argc, char const *argv[]) {
	
	vector<string> grid;
	
	int sr, sc;
	int er, ec;
	for(string line; getline(cin,line);) {
		int pos = line.find('S');
		if(pos != string::npos) {
			sr = grid.size();
			sc = pos; 
		}
		
		pos = line.find('E');
		if(pos != string::npos) {
			er = grid.size();
			ec = pos;
		}
		grid.push_back(line);
	}
	
	vector<vector<int>> dirs = {{-1,0}, {0,1}, {1,0} ,{0,-1}};
	
	queue<vector<int>> q;

	int dir;
	for(dir = 0; dir < (int)dirs.size(); ++dir) {
		if(grid[sr+dirs[dir][0]][sc+dirs[dir][1]] == '.') {
			break;
		}
	}
	
	q.push({0,sr,sc,dir});
	
	int R = grid.size();
	int C = grid[0].size();
	
	vector<vector<int>> dis(R, vector<int>(C, -1));
	
	while(!q.empty()) {
		auto vec = q.front(); q.pop();
		int time = vec[0];
		int r = vec[1];
		int c = vec[2];
		dir = vec[3];
		
		dis[r][c] = time;
		// path[r][c] = mp[dir];
		
		int nr = r + dirs[dir][0];
		int nc = c + dirs[dir][1];
		
		if(grid[nr][nc] != '#') {
			q.push({time+1, nr,nc,dir});
			continue;
		}
		
		int turns[] = {-1, 1};
		for(int t = 0; t < 2; ++t) {
			int ndir = ((dir + turns[t]) % 4 + 4) % 4;
			
			int nr = r + dirs[ndir][0];
			int nc = c + dirs[ndir][1];
			
			if(grid[nr][nc] != '#') {
				q.push({time,r,c, ndir});
			}
		}
	}
	
	for(dir = 0; dir < (int)dirs.size(); ++dir) {
		if(grid[sr+dirs[dir][0]][sc+dirs[dir][1]] == '.') {
			break;
		}
	}
	
	q.push({sr,sc,dir});
	
	// Time saved, count of cheats
	map<int,int> count;
	
	// Check for cheats
	while(!q.empty()) {
		auto vec = q.front(); q.pop();
		int r = vec[0];
		int c = vec[1];
		int d = vec[2];
		
		int time = dis[r][c];
		
		int nr = r + dirs[d][0];
		int nc = c + dirs[d][1];
		
		// Try to cheat
		for(int dr = -20; dr <= 20; ++dr) {
			for(int dc = -20; dc <= 20; ++dc) {
				if((abs(dr) + abs(dc)) <= 20) {
					
					int pr = r + dr;
					int pc = c + dc;	
					int cheatTime = abs(dr) + abs(dc);
					
					if(pr < R && pr >= 0 && pc < C && pc >= 0) {
						if(dis[pr][pc] > dis[r][c] + cheatTime) {
							int timeSaved = dis[pr][pc] - dis[r][c] - cheatTime;
							count[timeSaved]++;
						}
					}
				}
			}
		}
		
		
		if(dis[nr][nc] == time+1) {
			q.push({nr,nc,d});
			continue;
		}
		
		int turns[] = {-1, 1};
		for(int t = 0; t < 2; ++t) {
			int nd = ((d + turns[t]) % 4 + 4) % 4;
			
			int nr = r + dirs[nd][0];
			int nc = c + dirs[nd][1];
			
			if(dis[nr][nc] == time+1) {
				q.push({nr,nc,nd});
			}
		}
	}
	
	int threshold = 100;
	// for(auto& pr: count) {
	// 	if(pr.first >= threshold) {
	// 		if(pr.second == 1) {
	// 			printf("There is one cheat that saves %d picoseconds.\n", pr.first);
	// 			continue;
	// 		}
	// 		printf("There are %d cheats that save %d picoseconds.\n", pr.second, pr.first);
	// 	}
	// }
	
	int cheats = 0;
	for(auto& pr: count) {
		if(pr.first >= threshold) cheats += pr.second;
	}
	
	printf("%d\n", cheats);
	
	return 0;
}