#include <bits/stdc++.h>
using namespace std;


int main(int argc, char const *argv[]) {

	string edge;
	string u,v;
	
	map<string, vector<string>> adj;
	
	map<string, int> mp;
	vector<string> nodes;
	
	vector<int> tnodes;
	
	while(getline(cin,edge)) {
		for(auto& ch: edge) {
			int pos = edge.find('-');
			u = edge.substr(0,pos);
			v = edge.substr(pos+1);
		}
		
		if(mp.find(u) == mp.end()) {
			mp[u] = nodes.size();
			nodes.push_back(u);
			
			if(u[0] == 't') {
				tnodes.push_back(mp[u]);
			}
		}
		
		if(mp.find(v) == mp.end()) {
			mp[v] = nodes.size();
			nodes.push_back(v);
			
			if(v[0] == 't') {
				tnodes.push_back(mp[v]);
			}
		}
		
		adj[u].push_back(v);
		adj[v].push_back(u);
		
		// printf("%d %d\n", mp[u], mp[v]);
	}
	
	int N = nodes.size();
	vector<vector<int>> matrix(N, vector<int>(N,0));
	
	int adjNode;
	for(int node = 0; node < N; ++node) {
		for(string adjStr: adj[nodes[node]]) {
			adjNode = mp[adjStr];
			matrix[node][adjNode] = 1;
			matrix[adjNode][node] = 1;
		}
	}
	
	set<vector<int>> vis;
	int tcount = 0;
	for(int t: tnodes) {
		for(int u = 0; u < nodes.size(); ++u) {
			for(int v = u+1; v < nodes.size(); ++v) {
				
				if(t == u || t == v) continue;
				
				// edge t-u, t-v, u-v
				if(matrix[t][u] && matrix[t][v] && matrix[u][v]) {
					vector<int> vec = {t,u,v};
					sort(vec.begin(), vec.end());
					
					if(vis.find(vec) != vis.end()) continue;
					vis.insert(vec);
					
					tcount += 1;
				}
				
			}
		}
	}
	
	printf("%d\n", tcount);
	
	return 0;
}