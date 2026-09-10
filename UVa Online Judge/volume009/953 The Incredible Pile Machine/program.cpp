// The Incredible Pile Machine
// UVa ID: 953
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        int T;
        cin >> T;
        vector<vector<int>> P(T, vector<int>(T));
        int total = 0;
        for (int i = 0; i < T; ++i)
            for (int j = 0; j < T; ++j) {
                cin >> P[i][j];
                total += P[i][j];
            }
        vector<int> perm(T), bestPerm(T);
        for (int i = 0; i < T; ++i) perm[i] = i;
        int maxSave = -1;
        do {
            int save = 0;
            for (int i = 0; i < T; ++i) save += P[i][perm[i]];
            if (save > maxSave) {
                maxSave = save;
                bestPerm = perm;
            }
        } while (next_permutation(perm.begin(), perm.end()));
        int minOps = total - maxSave;
        for (int i = 0; i < T; ++i) cout << bestPerm[i];
        cout << " " << minOps << "\n";
    }
    return 0;
}
