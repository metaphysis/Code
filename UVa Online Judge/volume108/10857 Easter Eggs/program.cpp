#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, speed, i, j, k, mask, last, to, left, load, cnt, total, ans, newMask, curWid, nxtWid, curId, nxtId, rankLast, rankTo;
    double posX[17], posY[17], orgDis[17], sunTime[17], dis[17][17], powTwo[18], inf = 1e100, eps = 1e-9;
    powTwo[0] = 1;
    for (i = 1; i <= 17; i++)
        powTwo[i] = powTwo[i - 1] * 2;
    while (cin >> n >> speed) {
        if (n == 0 && speed == 0) break;
        for (i = 0; i < n; i++) {
            cin >> posX[i] >> posY[i];
            orgDis[i] = hypot(posX[i], posY[i]);
            sunTime[i] = 43200.0 + posX[i] * 0.03;
        }
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                dis[i][j] = hypot(posX[i] - posX[j], posY[i] - posY[j]);
        total = 1 << n;
        ans = 0;
        vector<double> home(total, inf), cur, nxt;
        vector<int> curPos(total, -1), nxtPos(total, -1);
        home[0] = 0;
        for (k = 0; k < n; k++) {
            nxt.clear();
            fill(nxtPos.begin(), nxtPos.end(), -1);
            nxtWid = n - k;
            for (mask = 0; mask < total; mask++) {
                if (__builtin_popcount(mask) != k) continue;
                nxtPos[mask] = -1;
            }
            for (mask = 0; mask < total; mask++) {
                if (__builtin_popcount(mask) != k + 1) continue;
                nxtPos[mask] = (int)nxt.size();
                cnt = __builtin_popcount(mask);
                nxt.resize(nxt.size() + cnt * nxtWid, inf);
            }
            curWid = n - k + 1;
            for (mask = 0; mask < total; mask++) {
                if (__builtin_popcount(mask) != k) continue;
                if (k > 0) {
                    for (last = 0; last < n; last++) {
                        if (!(mask & (1 << last))) continue;
                        rankLast = __builtin_popcount(mask & ((1 << last) - 1));
                        curId = curPos[mask] + rankLast * curWid;
                        if (cur[curId] + orgDis[last] / speed < home[mask])
                            home[mask] = cur[curId] + orgDis[last] / speed;
                    }
                }
                if (home[mask] < inf) {
                    for (to = 0; to < n; to++) {
                        if (mask & (1 << to)) continue;
                        newMask = mask | (1 << to);
                        rankTo = __builtin_popcount(mask & ((1 << to) - 1));
                        for (load = 1; load <= n - k; load++) {
                            double nextTime = home[mask] + orgDis[to] * powTwo[load] / speed;
                            if (nextTime + eps >= sunTime[to]) continue;
                            nxtId = nxtPos[newMask] + rankTo * nxtWid + load - 1;
                            if (nextTime < nxt[nxtId]) nxt[nxtId] = nextTime;
                            ans = max(ans, k + 1);
                        }
                    }
                }
                if (k == 0) continue;
                for (last = 0; last < n; last++) {
                    if (!(mask & (1 << last))) continue;
                    rankLast = __builtin_popcount(mask & ((1 << last) - 1));
                    for (left = 1; left < curWid; left++) {
                        curId = curPos[mask] + rankLast * curWid + left;
                        if (cur[curId] >= inf) continue;
                        for (to = 0; to < n; to++) {
                            if (mask & (1 << to)) continue;
                            double nextTime = cur[curId] + dis[last][to] * powTwo[left] / speed;
                            if (nextTime + eps >= sunTime[to]) continue;
                            newMask = mask | (1 << to);
                            rankTo = __builtin_popcount(mask & ((1 << to) - 1));
                            nxtId = nxtPos[newMask] + rankTo * nxtWid + left - 1;
                            if (nextTime < nxt[nxtId]) nxt[nxtId] = nextTime;
                            ans = max(ans, k + 1);
                        }
                    }
                }
            }
            cur.swap(nxt);
            curPos.swap(nxtPos);
        }
        cout << ans << '\n';
    }
    return 0;
}
