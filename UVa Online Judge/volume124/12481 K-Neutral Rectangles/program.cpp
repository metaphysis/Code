#include <bits/stdc++.h>
using namespace std;

long long solveCase(int n, int m, int k) {
    vector<int> pre(m), cur(m), ver(m), hor(m - 1);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> cur[j];
        for (int j = 0; j < m; j++) {
            if (i == 0) ver[j] = 1;
            else if (abs(cur[j] - pre[j]) <= k) ver[j]++;
            else ver[j] = 1;
        }
        for (int j = 1; j < m; j++) {
            if (abs(cur[j] - cur[j - 1]) <= k) hor[j - 1]++;
            else hor[j - 1] = 0;
        }
        int len = 2 * m - 1;
        vector<int> seq(len), lef(len), rig(len), stk;
        for (int j = 0; j < m; j++) {
            seq[2 * j] = ver[j];
            if (j > 0) seq[2 * j - 1] = hor[j - 1];
        }
        for (int p = 0; p < len; p++) {
            while (!stk.empty() && seq[stk.back()] >= seq[p])
                stk.pop_back();
            lef[p] = stk.empty() ? -1 : stk.back();
            stk.push_back(p);
        }
        stk.clear();
        for (int p = len - 1; p >= 0; p--) {
            while (!stk.empty() && seq[stk.back()] >= seq[p])
                stk.pop_back();
            rig[p] = stk.empty() ? len : stk.back();
            stk.push_back(p);
        }
        for (int p = 0; p < len; p += 2) {
            long long left = (lef[p] + 2) / 2;
            long long right = (rig[p] - 1) / 2;
            long long width = right - left + 1;
            ans = max(ans, width * seq[p]);
        }
        swap(pre, cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << "Case " << cs << ": " << solveCase(n, m, k) << '\n';
    }
    return 0;
}
