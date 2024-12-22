#include <bits/stdc++.h>
using namespace std;

map<int, vector<int>> graph;
map<int,int> indeg;
set<int> nodes;
vector<int> topoSort;
int midPageSum = 0;

void print(vector<int>& nums) {
	cout << "Vector Size: " << nums.size() << "\n";
	for(auto& num: nums) {
		cout << num << " ";
	}
	cout << "\n";
}

void print(map<int,int>& ump) {
	for(auto &pr: ump) {
		cout << pr.first << " " << pr.second << "\n";
	}
}

void print(set<int>& st) {
	cout << "Set Size: " << st.size() << "\n";
	for(auto& num: st) {
		cout << num << " ";
	}
	cout << "\n";
}

vector<int> bfs(int node) {
	map<int,int> visited;
	
	queue<int> q;
	q.push(node);
	
	vector<int> traversal;
	
	visited[node] = 1;
	
	while(!q.empty()) {
		int node = q.front(); q.pop();
		traversal.push_back(node);
		
		for(auto adjNode: graph[node]) {
			if(!visited[adjNode]) {
				visited[adjNode] = 1;
				q.push(adjNode);
			}
		}
	}
	return traversal;
}

void topologicalSort() {
	queue<int> q;
	
	for(auto node: indeg) {
		if(indeg[node.first] == 0) {
			q.push(node.first);
		}
	}
	
	while(!q.empty()) {
		int node = q.front(); q.pop();
		topoSort.push_back(node);
		
		for(auto adjNode: graph[node]) {
			indeg[adjNode] -= 1;
			if(indeg[adjNode] == 0) {
				q.push(adjNode);
			}
		}
	}
}

void addEdge(string& line) {
	int u = 0, v = 0;
	for(auto ch: line) {
		if(ch == '|') {
			u = v;
			v = 0;
			continue;
		}
		v *= 10;
		v += ch - '0';
	}
	
	graph[u].push_back(v);
	indeg[u] += 0;
	indeg[v] += 1;
	
	nodes.insert(u);
	nodes.insert(v);
}

void checkOrder(vector<int>& update) {
	int mid = update.size() / 2;
	
	int tidx = 0, uidx = 0;
	
	while(tidx < topoSort.size() && uidx < update.size()) {
		while(tidx < topoSort.size() && topoSort[tidx] != update[uidx]) {
			tidx++;
		}
		tidx++;
		uidx++;
	}
	
	if(uidx == update.size()) {
		// Correct Update Order
		midPageSum += update[mid];
	}
}

void handleUpdate(string& line) {
	int prevIdx = -1, idx = 0, num = 0;
	vector<int> update; 
	while((idx = line.find(",",idx+1)) != string::npos) {
		num = stoi(line.substr(prevIdx+1, idx-prevIdx-1));
		update.push_back(num);
		prevIdx = idx;
	}
	num = stoi(line.substr(prevIdx+1, line.size()-prevIdx-1));
	update.push_back(num);
	
	checkOrder(update);
}

void handleInput(string& line) {
	if(line.find("|") != string::npos) {
		addEdge(line);
	} else{
		// handleUpdate(line);
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	
	for(string line; getline(cin,line);) {
		if(line.size() != 0) {
			handleInput(line);
		} else {
			// topologicalSort();
		}
	}
	
	cout << midPageSum;

	return 0;
}