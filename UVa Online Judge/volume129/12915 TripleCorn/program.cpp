#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 62);
const int maxN = 10000 + 5;

int n, k;
long long a[maxN], pre[maxN], lastDp[maxN], curDp[maxN];

long long getCost(int l, int r) {
    int m = (l + r) / 2;
    long long leftCost = a[m] * (m - l + 1) - (pre[m] - pre[l - 1]);
    long long rightCost = (pre[r] - pre[m]) - a[m] * (r - m);
    return leftCost + rightCost;
}

void divideSolve(int layer, int left, int right, int optLeft, int optRight) {
    if (left > right)
        return;
    int mid = (left + right) / 2, bestPos = -1;
    long long bestValue = inf;
    int endPos = min(mid - 1, optRight);
    for (int pos = optLeft; pos <= endPos; ++pos) {
        long long value = lastDp[pos] + getCost(pos + 1, mid);
        if (value < bestValue) {
            bestValue = value;
            bestPos = pos;
        }
    }
    curDp[mid] = bestValue;
    divideSolve(layer, left, mid - 1, optLeft, bestPos);
    divideSolve(layer, mid + 1, right, bestPos, optRight);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> k) {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        int different = 1;
        for (int i = 2; i <= n; ++i)
            if (a[i] != a[i - 1])
                ++different;
        if (different <= k) {
            cout << 0 << '\n';
            continue;
        }
        pre[0] = 0;
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + a[i];
        for (int i = 0; i <= n; ++i)
            lastDp[i] = inf;
        lastDp[0] = 0;
        for (int group = 1; group <= k; ++group) {
            for (int i = 0; i <= n; ++i)
                curDp[i] = inf;
            divideSolve(group, group, n, group - 1, n - 1);
            for (int i = 0; i <= n; ++i)
                lastDp[i] = curDp[i];
        }
        cout << lastDp[n] << '\n';
    }
    return 0;
}
