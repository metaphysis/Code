// Be Efficient
// UVa ID: 11155
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, X[10010], cnt[10010];
    long long prefix[10010] = {0};
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        int A, B, C, M, N;
        cin >> A >> B >> C >> M >> N;
        X[0] = A;
        for (int i = 1; i < N; i++) X[i] = ((X[i - 1] * B + C) % M) + 1;
        for (int i = 1; i <= N; i++) prefix[i] = (prefix[i - 1] + X[i - 1]) % M;
        memset(cnt, 0, sizeof cnt);
        cnt[0] = 1;
        long long r = 0;
        for (int j = 0; j < N; j++) r += cnt[prefix[j + 1]]++;
        cout << "Case " << cs << ": " << r << "\n";
    }
    return 0;
}
