#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

void addBit(vector<int>& bit, int pos) {
    int n = bit.size() - 1;
    for (; pos <= n; pos += pos & -pos) bit[pos]++;
}

long long queryBit(const vector<int>& bit, int pos) {
    long long res = 0;
    for (; pos > 0; pos -= pos & -pos) res += bit[pos];
    return res;
}

long long solve(const vector<int>& a, int colorCnt) {
    int n = a.size() - 1, bound = max(1, (int)sqrt(n / log2(n + 1.0)));
    vector<int> freq(colorCnt, 0), bit(n + 1, 0);
    vector<long long> endCnt(n + 1, 0);
    vector<vector<int>> prevPos(colorCnt);
    long long ans = 0;
    for (int i = 1; i <= n; i++) freq[a[i]]++;
    // 统计两种轻颜色之间的交点
    for (int r = 1; r <= n; r++) {
        int c = a[r];
        endCnt[r] = endCnt[r - 1];
        if (freq[c] > bound) continue;
        int t = prevPos[c].size();
        for (int j = 0; j < t; j++) {
            int l = prevPos[c][j];
            long long ways = queryBit(bit, l - 1) - endCnt[l] - 1LL * j * (t - j - 1);
            ans = (ans + ways) % mod;
        }
        for (int l : prevPos[c]) addBit(bit, l);
        endCnt[r] += t;
        prevPos[c].push_back(r);
    }
    vector<long long> cnt(colorCnt), sumH(colorCnt), sumSq(colorCnt);
    // 固定重颜色，统计两种交错形式
    for (int h = 0; h < colorCnt; h++) {
        if (freq[h] <= bound) continue;
        fill(cnt.begin(), cnt.end(), 0);
        fill(sumH.begin(), sumH.end(), 0);
        fill(sumSq.begin(), sumSq.end(), 0);
        long long hCnt = 0, tripleCnt = 0;
        for (int i = 1; i <= n; i++) {
            int c = a[i];
            if (c == h) {
                ans = (ans + tripleCnt) % mod;
                hCnt++;
            } else {
                if (freq[c] > bound && c < h) continue;
                long long ways = hCnt * sumH[c] - sumSq[c];
                ans = (ans + ways) % mod;
                tripleCnt += cnt[c] * hCnt - sumH[c];
                cnt[c]++;
                sumH[c] += hCnt;
                sumSq[c] += hCnt * hCnt;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> a(n + 1), vals;
        vals.reserve(n);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            vals.push_back(a[i]);
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int i = 1; i <= n; i++) a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        cout << solve(a, vals.size()) << '\n';
    }
    return 0;
}
