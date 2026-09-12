#include <bits/stdc++.h>
using namespace std;

struct Result {
    double prob, avg;
};

int limitVal, per[4];
int money[15] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
int comb[16][16];
bool vis[1 << 15];
Result memo[1 << 15];

Result calc(int mask, int round) {
    if (vis[mask])
        return memo[mask];
    vis[mask] = true;
    int cnt = __builtin_popcount((unsigned)mask), sum = 0;
    for (int i = 0; i < 15; i++)
        if (mask & (1 << i))
            sum += money[i];
    int deal = sum * per[round - 1] / (100 * cnt);
    if (deal >= limitVal)
        return memo[mask] = {1.0, (double)deal};
    if (round == 4) {
        int good = 0;
        double avg = 0;
        for (int i = 0; i < 15; i++)
            if (mask & (1 << i)) {
                avg += money[i];
                if (money[i] >= limitVal)
                    good++;
            }
        return memo[mask] = {(double)good / 2.0, avg / 2.0};
    }
    int openCnt = 3, nextCnt = cnt - openCnt;
    double trans = (double)nextCnt / (cnt * comb[cnt - 1][openCnt]);
    double prob = 0, avg = 0;
    for (int nextMask = mask; nextMask; nextMask = (nextMask - 1) & mask) {
        if (__builtin_popcount((unsigned)nextMask) != nextCnt)
            continue;
        Result temp = calc(nextMask, round + 1);
        prob += trans * temp.prob;
        avg += trans * temp.avg;
    }
    return memo[mask] = {prob, avg};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i <= 15; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
    while (cin >> limitVal && limitVal) {
        for (int i = 0; i < 4; i++)
            cin >> per[i];
        memset(vis, 0, sizeof(vis));
        int fullMask = (1 << 15) - 1, nextCnt = 11;
        double trans = (double)nextCnt / (15.0 * comb[14][4]);
        double prob = 0, avg = 0;
        for (int nextMask = fullMask; nextMask; nextMask = (nextMask - 1) & fullMask) {
            if (__builtin_popcount((unsigned)nextMask) != nextCnt)
                continue;
            Result temp = calc(nextMask, 1);
            prob += trans * temp.prob;
            avg += trans * temp.avg;
        }
        cout << fixed << setprecision(6) << prob << " ";
        cout << fixed << setprecision(2) << avg << "\n";
    }
    return 0;
}
