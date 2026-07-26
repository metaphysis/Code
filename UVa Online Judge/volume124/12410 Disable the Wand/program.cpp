// Disable the Wand
// UVa ID: 12410
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.080s
// https://blog.csdn.net/metaphysis/article/details/163217735

#include <bits/stdc++.h>
using namespace std;

// 全局参数
int gMaxOne, gIdeal, gK, gN;
int gIdealBit[32];
long long gPow2[32];

// 记忆化数组，维度：[pos][cnt1][diff][mod3][mod7]
long long gDpCnt[32][33][33][3][7];
long long gDpSum[32][33][33][3][7];

// 返回 pair<个数, 和>
pair<long long, long long> dfs(int pos, int cnt1, int diff, int mod3, int mod7, bool tight) {
    if (cnt1 > gMaxOne || diff > gK) return make_pair(0, 0);
    if (pos < 0) {
        if (mod3 == 0 && mod7 != 0) return make_pair(1, 0);
        return make_pair(0, 0);
    }
    if (!tight) {
        long long &cnt = gDpCnt[pos][cnt1][diff][mod3][mod7];
        if (cnt != -1) return make_pair(cnt, gDpSum[pos][cnt1][diff][mod3][mod7]);
    }
    int limit = tight ? ((gN >> pos) & 1) : 1;
    long long totalCnt = 0, totalSum = 0;
    for (int bit = 0; bit <= limit; ++bit) {
        int newCnt1 = cnt1 + bit;
        int newDiff = diff + (bit != gIdealBit[pos]);
        int newMod3 = (mod3 * 2 + bit) % 3;
        int newMod7 = (mod7 * 2 + bit) % 7;
        pair<long long, long long> child = dfs(pos - 1, newCnt1, newDiff, newMod3, newMod7, tight && (bit == limit));
        long long c = child.first, s = child.second;
        totalCnt += c;
        if (bit) totalSum += gPow2[pos] * c + s;
        else totalSum += s;
    }
    if (!tight) {
        gDpCnt[pos][cnt1][diff][mod3][mod7] = totalCnt;
        gDpSum[pos][cnt1][diff][mod3][mod7] = totalSum;
    }
    return make_pair(totalCnt, totalSum);
}

long long solve(int n) {
    if (n < 0) return 0;
    gN = n;
    return dfs(31, 0, 0, 0, 0, true).second;
}

int main() {
    // 预计算 2^pos
    for (int i = 0; i < 32; ++i) gPow2[i] = 1LL << i;
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int start, end, maxOne, ideal, k;
        scanf("%d %d %d %d %d", &start, &end, &maxOne, &ideal, &k);
        gMaxOne = maxOne;
        gIdeal = ideal;
        gK = k;
        for (int i = 0; i < 32; ++i) gIdealBit[i] = (ideal >> i) & 1;
        // 重置记忆化数组
        memset(gDpCnt, -1, sizeof(gDpCnt));
        // 注意：gDpSum 不需要重置，因为只有 gDpCnt != -1 时才会读取
        long long ans = solve(end) - solve(start - 1);
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
