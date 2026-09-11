// Gnirut
// UVa ID: 11712
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N && N != 0) {
        vector<string> verdicts(N);
        bool hasTle = false, hasMle = false;
        for (int i = 0; i < N; ++i) {
            cin >> verdicts[i];
            if (verdicts[i] == "TLE") hasTle = true;
            if (verdicts[i] == "MLE") hasMle = true;
        }
        vector<int> xs(N), ys(N);
        int nextX = 3;
        int maxX = 0;
        for (int i = 0; i < N; ++i) {
            if (verdicts[i] == "AC") {
                xs[i] = nextX++;
                ys[i] = xs[i];
            } else if (verdicts[i] == "WA") {
                xs[i] = nextX++;
                ys[i] = (xs[i] == 1000 ? 1 : xs[i] + 1);
            } else if (verdicts[i] == "TLE") {
                xs[i] = 1;
                ys[i] = 1;
            } else { // MLE
                xs[i] = 998;
                ys[i] = 1;
            }
            maxX = max(maxX, xs[i]);
        }
        int M = maxX;
        if (hasTle) ++M;
        if (hasMle) ++M;
        cout << M << ' ' << N << '\n';
        for (int i = 0; i < maxX; ++i)
            cout << i << " 1 " << i + 1 << " 1 R\n";
        if (hasTle)
            cout << "1 0 0 0 L\n";
        if (hasMle)
            cout << maxX << " 0 " << maxX << " 0 R\n";
        for (int i = 0; i < N; ++i)
            cout << xs[i] << ' ' << ys[i] << '\n';
    }
    return 0;
}
