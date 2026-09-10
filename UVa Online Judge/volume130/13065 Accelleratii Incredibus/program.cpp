#include <bits/stdc++.h>
using namespace std;

const int MaxL = 1005;
const long long Inf = 1LL << 60;

long long dp[MaxL], newDp[MaxL];
int que[MaxL];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, xi, xf, m, v;
    string bomb;
    while (cin >> l && l != 0) {
        cin >> xi >> xf;
        cin >> m >> v;
        for (int i = 0; i <= l; i++) dp[i] = Inf;
        dp[xi] = 0;
        for (int minute = 1; minute <= m; minute++) {
            cin >> bomb;
            for (int i = 0; i <= l; i++) newDp[i] = Inf;
            int pos = 0;
            while (pos <= l) {
                if (bomb[pos] == 'X') {
                    pos++;
                    continue;
                }
                int left = pos;
                while (pos <= l && bomb[pos] == '.') pos++;
                int right = pos - 1;
                int head = 0, tail = 0;
                for (int q = left; q <= right; q++) {
                    while (head < tail && que[head] < q - v) head++;
                    if (dp[q] < Inf) {
                        long long value = dp[q] - q;
                        while (head < tail && dp[que[tail - 1]] - que[tail - 1] >= value) tail--;
                        que[tail++] = q;
                    }
                    if (head < tail) newDp[q] = min(newDp[q], dp[que[head]] + q - que[head]);
                }
                head = 0;
                tail = 0;
                for (int q = right; q >= left; q--) {
                    while (head < tail && que[head] > q + v) head++;
                    if (dp[q] < Inf) {
                        long long value = dp[q] + q;
                        while (head < tail && dp[que[tail - 1]] + que[tail - 1] >= value) tail--;
                        que[tail++] = q;
                    }
                    if (head < tail) newDp[q] = min(newDp[q], dp[que[head]] + que[head] - q);
                }
            }
            for (int i = 0; i <= l; i++) dp[i] = newDp[i];
        }
        if (dp[xf] >= Inf) cout << -1 << '\n';
        else cout << dp[xf] << '\n';
    }
    return 0;
}
