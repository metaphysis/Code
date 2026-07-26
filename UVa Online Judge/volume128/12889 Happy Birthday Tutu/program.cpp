// Happy Birthday Tutu
// UVa ID: 12889
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163220977

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;
        int first;
        cin >> first;
        bool allSame = true;
        for (int i = 1; i < K; ++i) {
            int x;
            cin >> x;
            if (x != first) allSame = false;
        }
        if (allSame) cout << "Better luck next time!\n";
        else cout << "Happy Birthday Tutu!\n";
    }
    return 0;
}
