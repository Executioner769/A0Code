#include <bits/stdc++.h>
using namespace std;

int arr[7][7][7][7][7];

void prefixSum() {
    for(int w = 0; w < 5; ++w) {
        for(int a = 0; a < 6; ++a) {
            for(int b = 0; b < 6; ++b) {
                for(int c = 0; c < 6; ++c) {
                    for(int d = 0; d < 6; ++d) {
                        for(int e = 0; e < 6; ++e) {
                            arr[a+(w==0)][b+(w==1)][c+(w==2)][d+(w==3)][e+(w==4)] += arr[a][b][c][d][e];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {

    vector<vector<int>> A;
    char s[16];
    while(scanf(" %s", s) != EOF) {
        vector<string> grid;
        grid.push_back(string(s));

        for(int i = 0; i < 6; ++i) {
            scanf(" %s", s);
            grid.push_back(string(s));
        }
        vector<int> v;
        for(int c = 0; c < 5; ++c) {
            int cnt = 0;
            for(int r = 0; r < 7; ++r) {
                if(grid[r][c] == '#') {
                    cnt++;
                }
            }
            v.push_back(cnt-1);
        }

        if(grid[0][0] == '#') {
            A.push_back(v);
        } else {
            arr[v[0]][v[1]][v[2]][v[3]][v[4]]++;
        }
    }

    prefixSum();
    int answer = 0;
    for(auto& v: A) {
        answer += arr[5-v[0]][5-v[1]][5-v[2]][5-v[3]][5-v[4]];
    }

    printf("%d\n", answer);

    return 0;
}
