#include <bits/stdc++.h>
using namespace std;

map<int, vector<int>> graph;
int midPageSum = 0, midPageSumPart2 = 0;

void topoSort(int node, vector<int>& topo, const set<int>& updateNodes, map<int,int>& indeg) {
	topo.push_back(node);
	for(auto adjNode: graph[node]) {
		if(updateNodes.count(adjNode)) {
			if(--indeg[adjNode] == 0) {
				topoSort(adjNode, topo, updateNodes, indeg);
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
}

void checkOrder(vector<int>& update) {
	bool isValid = true;
	// Maintain a visited set that tells me if a node is visited before
	set<int> visited;
	
	// set of all nodes in the update list
	set<int> updateNodes(update.begin(), update.end());
	
	// indegree of the nodes
	map<int,int> indeg;
	
	// Iterate through each node of update and check if any of the adjNode appear previously in the update array. It is not a valid order.
	for(int i = 0; i < update.size(); ++i) {
		int node = update[i];
		for(auto adjNode: graph[node]) {
			
			if(updateNodes.count(adjNode)) {
				++indeg[adjNode];
			}
			
			if(visited.count(adjNode)) {
				isValid = false;
			}
		}
		visited.insert(node);
	}
	
	int mid;
	if(isValid) {
		mid = update.size() / 2;
		midPageSum += update[mid];
	} else {
		// Part 2
		// Fix the ordering of the update.
		vector<int> topo;
		
		vector<int> statNodes;
		
		for(auto node: update) {
			if(indeg[node] == 0) {
				statNodes.push_back(node);
			}
		}
		
		for(auto node: statNodes) {
			topoSort(node,topo,updateNodes,indeg);
		}
		
		mid = topo.size() / 2;
		midPageSumPart2 += topo[mid];
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
		handleUpdate(line);
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
		}
	}
	
	cout << midPageSum << "\n";
	cout << midPageSumPart2 << "\n";

	return 0;
}