#include <bits/stdc++.h>
using namespace std;

const long long mod = (1LL << 30);

long long getMax(long long n, long long m) {
    long long val = 0;
    bool tight = true;
    for (int bit = 60; bit >= 0; bit--) {
        int nBit = (n >> bit) & 1, mBit = (m >> bit) & 1;
        int want = nBit ^ 1, cur;
        if (!tight || want <= mBit) cur = want;
        else cur = 0;
        if (cur) val |= 1LL << bit;
        if (tight && cur < mBit) tight = false;
    }
    return n ^ val;
}

long long calcSum(long long n, long long limY, long long limX) {
    long long cnt[2][2] = {}, sum[2][2] = {};
    cnt[1][1] = 1;
    for (int bit = 60; bit >= 0; bit--) {
        long long nextCnt[2][2] = {}, nextSum[2][2] = {};
        long long bitVal = (1LL << bit) % mod;
        int nBit = (n >> bit) & 1, yBit = (limY >> bit) & 1, xBit = (limX >> bit) & 1;
        for (int tightY = 0; tightY <= 1; tightY++) {
            for (int tightX = 0; tightX <= 1; tightX++) {
                if (!cnt[tightY][tightX]) continue;
                for (int curBit = 0; curBit <= 1; curBit++) {
                    int xorBit = curBit ^ nBit;
                    if (tightY && curBit > yBit) continue;
                    if (tightX && xorBit > xBit) continue;
                    int nextY = tightY && (curBit == yBit), nextX = tightX && (xorBit == xBit);
                    nextCnt[nextY][nextX] = (nextCnt[nextY][nextX] + cnt[tightY][tightX]) % mod;
                    nextSum[nextY][nextX] = (nextSum[nextY][nextX] + sum[tightY][tightX] + curBit * bitVal % mod * cnt[tightY][tightX]) % mod;
                }
            }
        }
        memcpy(cnt, nextCnt, sizeof(cnt));
        memcpy(sum, nextSum, sizeof(sum));
    }
    long long ans = 0;
    for (int tightY = 0; tightY <= 1; tightY++)
        for (int tightX = 0; tightX <= 1; tightX++) ans = (ans + sum[tightY][tightX]) % mod;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    for (int caseNum = 1; caseNum <= testNum; caseNum++) {
        long long n, m, res1, totalSum, smallSum, res2;
        cin >> n >> m;
        res1 = getMax(n, m);
        totalSum = calcSum(n, (1LL << 61) - 1, res1);
        smallSum = calcSum(n, m, res1);
        res2 = (totalSum - smallSum + mod) % mod;
        cout << "Case " << caseNum << ": " << res1 << " " << res2 << "\n";
    }
    return 0;
}
