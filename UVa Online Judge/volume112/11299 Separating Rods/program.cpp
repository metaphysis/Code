#include <bits/stdc++.h>
using namespace std;
const int MOD = 10007;

bool checkOk(int x, const vector<int>& a, int k) {
    int cnt = 0, sum = 0;
    for (int v : a) {
        if (v > x) return false;
        if (sum + v > x) { ++cnt; sum = v; }
        else sum += v;
    }
    return cnt <= k;
}

int countWays(int x, const vector<int>& a, int k) {
    int n = (int)a.size();
    if (n == 0) return 1;
    vector<int> L(n + 1);
    int left = 1, curSum = 0;
    for (int i = 1; i <= n; ++i) {
        curSum += a[i - 1];
        while (curSum > x) { curSum -= a[left - 1]; ++left; }
        L[i] = left;
    }
    int maxSeg = min(k, n - 1) + 1;
    vector<int> prev(n + 1, 0), cur(n + 1, 0), pref(n + 1, 0);
    prev[0] = 1;
    int ans = 0;
    for (int seg = 1; seg <= maxSeg; ++seg) {
        pref[0] = prev[0];
        for (int i = 1; i <= n; ++i) pref[i] = (pref[i - 1] + prev[i]) % MOD;
        cur[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int l = L[i];
            if (l > i) { cur[i] = 0; continue; }
            int low = l - 1;
            int high = i - 1;
            int val = pref[high];
            if (low - 1 >= 0) val = (val - pref[low - 1] + MOD) % MOD;
            cur[i] = val;
        }
        ans = (ans + cur[n]) % MOD;
        prev.swap(cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (n == 0) { cout << "0 1\n"; continue; }
        long long sum = 0;
        int mx = 0;
        for (int v : a) { sum += v; mx = max(mx, v); }
        int lo = mx, hi = (int)sum;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (checkOk(mid, a, k)) hi = mid;
            else lo = mid + 1;
        }
        int ansX = lo;
        int ways = countWays(ansX, a, k);
        cout << ansX << " " << ways << "\n";
    }
    return 0;
}
