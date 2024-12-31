#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(int argc, char const *argv[]) {
	
	string line;
	// node Index to val map
	map<int, int> values;
	
	// node string to index map
	map<string, int> mp;
	// index to node string
	vector<string> nodes;
	
	string node;
	int val;
	while(getline(cin, line)) {
		
		if(line.size() == 0) break;
	
		int pos = line.find(':');
		if(pos != string::npos) {
			node = line.substr(0, pos);
			val = line.back() - '0';
			
			if(mp.find(node) == mp.end()) {
				mp[node] = nodes.size();
				nodes.push_back(node);
			}
			
			values[mp[node]] = val;
		}	
	}
	
	map<string, int> ops = {
		{"AND", 1},
		{"OR", 2},
		{"XOR", 3}
	};
	
	char str[8];
	string u, op1, v, op2, w; 
	// u --> v weight = op1
	// v --> w weight = op2
	
	// u op v w
	vector<vector<int>> edges;
	
	while(scanf(" %s", &str) != EOF) {
		u = string(str);
		
		if(mp.find(u) == mp.end()) {
			mp[u] = nodes.size();
			nodes.push_back(u);
		}
		
		scanf(" %s", &str);
		op1 = string(str);
		
		scanf(" %s", &str);
		v = string(str);
		
		if(mp.find(v) == mp.end()) {
			mp[v] = nodes.size();
			nodes.push_back(v);
		}
		
		// Ignore op2
		scanf(" %s", &str);
		op2 = string(str);
		
		scanf(" %s", &str);
		w = string(str);
		
		if(mp.find(w) == mp.end()) {
			mp[w] = nodes.size();
			nodes.push_back(w);
		}
		
		// Perform u op1 v if possible
		if(values.find(mp[u]) != values.end() && values.find(mp[v]) != values.end()) {
			int op = ops[op1];
			
			if(op == 1) {
				// AND
				values[mp[w]] = values[mp[u]] & values[mp[v]];
			} else if(op == 2) {
				// OR
				values[mp[w]] = values[mp[u]] | values[mp[v]];
			} else if(op == 3) {
				// XOR
				values[mp[w]] = values[mp[u]] ^ values[mp[v]];
			}
		} else {
			
			vector<int> edge;
			edge.push_back(mp[u]);
			edge.push_back(ops[op1]);
			edge.push_back(mp[v]);
			edge.push_back(mp[w]);	
			
			edges.push_back(edge);
		}
		
	}
	
	while(!edges.empty()) {
		
		vector<vector<int>> remaining;
		
		for(int idx = 0; idx < edges.size(); ++idx) {
			int u = edges[idx][0];
			int op = edges[idx][1];
			int v = edges[idx][2];
			int w = edges[idx][3];
			
			if(values.find(u) != values.end() && values.find(v) != values.end()) {
				if(op == 1) {
					values[w] = values[u] & values[v];
				} else if(op == 2) {
					values[w] = values[u] | values[v];
				} else if(op == 3) {
					values[w] = values[u] ^ values[v];
				}
			} else {
				remaining.push_back(edges[idx]);
			}
		}
		
		edges = remaining;
	}
	
	int n = nodes.size();
	
	ll number = 0;
	ll pow2 = 1;
	
	map<string, int> zNum;
	
	for(auto& pr: values) {
		int node = pr.first;
		int val = pr.second;
		if(nodes[node].front() == 'z') {
			zNum[nodes[node]] = val;
		}
	}
	
	for(auto& zpr: zNum) {
		if(zpr.second) {
			number += pow2;
		}
		pow2 <<= 1;
	}
	
	printf("%lld\n", number);

	return 0;
}