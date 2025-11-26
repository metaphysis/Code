// Set of Marbles
// UVa ID: 11535
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, b1;
    cin >> n >> b1;
    vector<int> initial(b1);
    for (int i = 0; i < b1; i++) cin >> initial[i];
    
    int startState = 0;
    for (int x : initial) startState |= (1 << (x - 1));
    
    int total = 1 << n;
    vector<int> visited(total, 0);
    vector<int> sequence;
    sequence.push_back(startState);
    visited[startState] = 1;
    
    while (sequence.size() < total) {
        int current = sequence.back();
        for (int i = 0; i < n; i++) {
            int next = current ^ (1 << i);
            if (!visited[next]) {
                sequence.push_back(next);
                visited[next] = 1;
                break;
            }
        }
    }
    
    for (int i = 0; i < total - 1; i++) {
        int changed = sequence[i] ^ sequence[i + 1];
        int marble = __builtin_ffs(changed);
        if (sequence[i] & changed)
            cout << "Move " << marble << " from B1 to B2\n";
        else
            cout << "Move " << marble << " from B2 to B1\n";
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
