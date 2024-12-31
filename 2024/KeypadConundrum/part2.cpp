#include <bits/stdc++.h>
using namespace std;

using Point = pair<int,int>;

struct Keypad {

    map<char, Point> chMap;
    map<Point, char> poMap;

    // Current Key Position
    int row, col;

    Keypad(vector<string> grid) {
        int rows = grid.size();
        int cols = grid[0].length();

        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < cols; ++c) {
                char key = grid[r][c];
                chMap[key] = {r,c};
                poMap[{r,c}] = key;

                if(key == 'A') {
                    row = r;
                    col = c;
                }
            }
        }
    }

    bool isValidPath(string& path) {
        int nr = row;
        int nc = col;

        for(char& dir: path) {
            if(dir == '^') {
                nr -= 1;
            } else if(dir == '>') {
                nc += 1;
            } else if(dir == 'v') {
                nr += 1;
            } else if(dir == '<') {
                nc -= 1;
            }

            if(poMap[{nr,nc}] == '#') return false;
        }

        return true;
    }

    void moveToKey(char key) {
        Point p = chMap[key];
        row = p.first;
        col = p.second;
    }

    vector<string> getPathsToKey(char key) {
        string path;

        Point p = chMap[key];
        int nrow = p.first;
        int ncol = p.second;

        // cold ..... cnew
        if(ncol > col) {
            path += string(ncol-col,'>');
        }

        // cnew ...... cold
        if(ncol < col) {
            path += string(col-ncol,'<');
        }

        // rold
        // ....
        // rnew
        if(nrow > row) {
            path += string(nrow-row,'v');
        }

        // rnew
        // ....
        // rold
        if(nrow < row) {
            path += string(row-nrow,'^');
        }

        vector<string> paths;
        sort(path.begin(), path.end());

        do {
            if(isValidPath(path)) {
                paths.push_back(path + "A");
            }
        } while(next_permutation(path.begin(), path.end()));

        return paths;
    }

};

uint64_t findMinLength(const string& sequence, int depth, const int maxDepth,  map<pair<int, string>, uint64_t>& cache) {

    if(depth == maxDepth) {
        return sequence.length();
    }

    const auto ptr = cache.find({depth, sequence});
    if(ptr != cache.end()) {
        return ptr->second;
    }

    uint64_t totalLen{};

    vector<string> dirGrid = { "#^A", "<v>"};
    Keypad dirpad(dirGrid);

    for(char key: sequence) {
        vector<string> pathsToKey = dirpad.getPathsToKey(key);
        dirpad.moveToKey(key);

        uint64_t minLen = numeric_limits<uint64_t>::max();

        for(const auto& path: pathsToKey) {
            uint64_t len = findMinLength(path, depth+1, maxDepth, cache);
            minLen = min(minLen, len);
        }

        totalLen += minLen;
    }

    cache[{depth,sequence}] = totalLen;
    return totalLen;
}

uint64_t findMinLength(const string& code, int maxDepth) {
    vector<string> numGrid = {"789","456","123","#0A"};

    Keypad numpad(numGrid);

    vector<string> totalPaths;

    totalPaths.push_back("");

    for(const char& key: code) {
        vector<string> pathsToKey = numpad.getPathsToKey(key);
        numpad.moveToKey(key);

        vector<string> newPaths;

        for(const auto& path: totalPaths) {
            for(const auto& keyPath: pathsToKey) {
                newPaths.push_back(path + keyPath);
            }
        }

        totalPaths = newPaths;
    }

    map<pair<int,string>, uint64_t> cache;

    uint64_t minLen = numeric_limits<uint64_t>::max();

    for(const auto& path: totalPaths) {
        uint64_t len = findMinLength(path, 0, maxDepth, cache);
        minLen = min(minLen, len);
    }

    return minLen;
}


int main(int argc, char const *argv[]) {

    string code;
    uint64_t total = 0l;
    while(getline(cin,code)) {
        uint64_t len = findMinLength(code,25);
        uint64_t complexity = len * stoull(code.substr(0,3));
        cout << code << " " << len << "\n";
        total += complexity;
    }

    cout << total << "\n";

    return 0;
}
