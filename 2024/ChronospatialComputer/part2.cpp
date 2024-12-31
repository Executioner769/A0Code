#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Only for given input program;
// 2,4,1,1,7,5,1,5,4,0,5,5,0,3,3,0

// {newA, out}
pair<ll,int> nextState(ll a) {
    ll b = a & 7;
    b ^= 1;
    ll c = a >> b;
    b ^= 5;
    b ^= c;
    int out = b & 7;
    a >>= 3;
    return {a,out};
}

void runMachine(const ll start, const vector<ll>& program) {
    ll a = start;
    while(a != 0) {
        auto pr = nextState(a);
        a = pr.first;
        int out = pr.second;
        printf("%d ", out);
    }
}

ll solve(const vector<ll>& program) {

    ll count = 0;

    queue<pair<int,ll>> q;

    q.push({program.size(),0});

    vector<ll> valid;

    while(!q.empty()) {
        auto state = q.front(); q.pop();
        int index = state.first;
        ll prevAValue = state.second;

        if(index == 0) {
            valid.push_back(prevAValue);
            continue;
        }

        int nextIndex = index - 1;
        ll lastOp = program[nextIndex];

        for(ll a = 0; a < 8; ++a) {

            count++;

            ll nextAValue = (prevAValue << 3) | a;

            auto pr = nextState(nextAValue);
            ll newAValue = pr.first;
            int out = pr.second;

            if(out == lastOp && newAValue == prevAValue) {
                // a is the right candidate

                // printf("%lld %lld %d\n", nextValue, prevAValue, lastOp);

                q.push({nextIndex, nextAValue});
            }
        }

    }

    printf("Iterations: %lld\n", count);

    return *min_element(valid.begin(), valid.end());

}

int main(int argc, char const *argv[]) {

    // TODO: dynamically read the program
    vector<ll> program = {2,4,1,1,7,5,1,5,4,0,5,5,0,3,3,0};

    ll a = solve(program);

    printf("A: %lld\n", a);

    // runMachine(a,program);

    return 0;
}
