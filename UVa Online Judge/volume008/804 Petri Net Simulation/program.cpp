// Petri Net Simulation
// UVa ID: 804
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.240s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct Transition { vector<int> input, output; };
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int NP, T = 1;
    while (cin >> NP && NP) {
        vector<int> places(NP + 1);
        for (int i = 1; i <= NP; i++) cin >> places[i];
        int NT;
        cin >> NT;
        vector<Transition> ts(NT + 1);
        for (int t = 1; t <= NT; t++) {
            int x;
            while (cin >> x && x) {
                if (x < 0) ts[t].input.push_back(-x);
                else ts[t].output.push_back(x);
            }
        }
        int NF;
        cin >> NF;
        int fired = 0, live = 1;
        for (; fired < NF; fired++) {
            int enabled = -1;
            for (int t = 1; t <= NT; t++) {
                vector<int> cnt(NP + 1, 0);
                for (int p : ts[t].input) cnt[p]++;
                bool canFired = true;
                for (int i = 1; i <= NP && canFired; i++)
                    if (places[i] < cnt[i]) canFired = false;
                if (canFired) { enabled = t; break; }
            }
            if (enabled == -1) { live = 0; break; }
            for (int p : ts[enabled].input) places[p]--;
            for (int p : ts[enabled].output) places[p]++;
        }
        cout << "Case " << T << ": ";
        if (live) cout << "still live after " << NF << " transitions\n";
        else cout << "dead after " << fired << " transitions\n";
        cout << "Places with tokens:";
        for (int i = 1; i <= NP; i++)
            if (places[i] > 0) cout << " " << i << " (" << places[i] << ")";
        cout << "\n\n";
        T++;
    }
    return 0;
}
