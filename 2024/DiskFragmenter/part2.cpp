#include <bits/stdc++.h>
using namespace std;

struct Block {
	int id, size, pos;
};

long long calculateCheckSum(vector<Block> blocks) {
	long long checkSum = 0;
	
	while(!blocks.empty()) {
		Block block = blocks.back();
		bool inserted = false;
		// Attempt to move the block if possible then move and pop
		for(int i = 0; i < (int)blocks.size()-1; ++i) {
			int prevBlockEndPos = blocks[i].pos + blocks[i].size;
			int nextBlockStartPos = blocks[i+1].pos;
			
			if(nextBlockStartPos - prevBlockEndPos >= block.size) {
				// Insert the block
				inserted = true;
				block.pos = prevBlockEndPos;
				blocks.insert(blocks.begin() + i+1, block);
				blocks.pop_back();
				break;
			}
		}
		
		// Compute the checkSum and pop
		if(!inserted) {
			blocks.pop_back();
			for(int i = 0; i < block.size; ++i) {
				checkSum += (block.pos + i) * block.id;
			}
		}
	}
	return checkSum;
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	string disk;
	cin >> disk;
	
	vector<Block> blocks;
	int n = disk.length(), pos = 0;
	for(int i = 0; i < n; ++i) {
		int size = disk[i] - '0';
		if(i % 2 == 0) {
			blocks.push_back(Block{i/2,size,pos});
		}
		pos += size;
	}
	
	cout << calculateCheckSum(blocks) << "\n";

	return 0;
}


// As mentioned by "Errichto Algorithms"
// The optimised way to find the left most gap for given block size is to use s Segment Tree (MAX)
// As the gap can range from 0 to 9 we can maintain
// set<int> gaps[10] 