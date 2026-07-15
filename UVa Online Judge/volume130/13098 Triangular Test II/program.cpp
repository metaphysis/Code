// Triangular Test II
// UVa ID: 13098
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 1.370s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MAXN = 10000000;
    const int MAX_TRI = 5000;

    int triNumbers[MAX_TRI];
    bool isTri[MAXN + 1] = {false};
    bool twoSum[MAXN + 1] = {false};

    int cnt = 0;
    int t = 0;
    for (int x = 1; ; ++x) {
        t += x;
        if (t > MAXN) break;
        triNumbers[cnt++] = t;
        isTri[t] = true;
    }

    for (int i = 0; i < cnt; ++i) {
        for (int j = i; j < cnt; ++j) {
            int sum = triNumbers[i] + triNumbers[j];
            if (sum > MAXN) break;
            twoSum[sum] = true;
        }
    }

    int N;
    while (cin >> N) {
        if (isTri[N]) cout << 1 << '\n';
        else if (twoSum[N]) cout << 2 << '\n';
        else cout << 3 << '\n';
    }
    return 0;
}
