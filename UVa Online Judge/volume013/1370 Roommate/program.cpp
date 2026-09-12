#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int facilityCount, na, nb;
        cin >> facilityCount;
        vector<int> pa(facilityCount + 1), pb(facilityCount + 1);
        for (int i = 1; i <= facilityCount; i++) cin >> pa[i];
        for (int i = 1; i <= facilityCount; i++) cin >> pb[i];
        cin >> na >> nb;
        vector<int> sa(na), sb(nb), daTime(na), dbTime(nb);
        for (int i = 0; i < na; i++) cin >> sa[i];
        for (int i = 0; i < nb; i++) cin >> sb[i];
        for (int i = 0; i < na; i++) daTime[i] = pa[sa[i]];
        for (int i = 0; i < nb; i++) dbTime[i] = pb[sb[i]];
        int width = nb + 1, stateCount = (na + 1) * (nb + 1), inf = 65535;
        vector<unsigned short> freeDp(stateCount, inf);
        vector<unsigned short> aRun(stateCount * 101, inf);
        vector<unsigned short> bRun(stateCount * 101, inf);
        auto relax = [&](vector<unsigned short>& dp, int pos, int value) {
            if (value < dp[pos]) dp[pos] = value;
        };
        freeDp[0] = 0;
        for (int sum = 0; sum <= na + nb; sum++) {
            int left = max(0, sum - nb), right = min(na, sum);
            for (int a = left; a <= right; a++) {
                int b = sum - a, pos = a * width + b;
                int cur = freeDp[pos];
                if (cur < inf) {
                    if (a < na) relax(freeDp, (a + 1) * width + b, cur + daTime[a]);
                    if (b < nb) relax(freeDp, a * width + b + 1, cur + dbTime[b]);
                    if (a < na && b < nb && sa[a] != sb[b]) {
                        int x = daTime[a], y = dbTime[b];
                        if (x < y) relax(bRun, ((a + 1) * width + b) * 101 + y - x, cur + x);
                        else if (x > y) relax(aRun, (a * width + b + 1) * 101 + x - y, cur + y);
                        else relax(freeDp, (a + 1) * width + b + 1, cur + x);
                    }
                }
                for (int remain = 1; remain <= 100; remain++) {
                    cur = aRun[pos * 101 + remain];
                    if (cur < inf) {
                        relax(freeDp, (a + 1) * width + b, cur + remain);
                        if (b < nb) {
                            int useTime = dbTime[b];
                            if (sa[a] != sb[b]) {
                                if (useTime < remain) relax(aRun, (a * width + b + 1) * 101 + remain - useTime, cur + useTime);
                                else if (useTime > remain) relax(bRun, ((a + 1) * width + b) * 101 + useTime - remain, cur + remain);
                                else relax(freeDp, (a + 1) * width + b + 1, cur + remain);
                            } else {
                                relax(bRun, ((a + 1) * width + b) * 101 + useTime, cur + remain);
                            }
                        }
                    }
                    cur = bRun[pos * 101 + remain];
                    if (cur < inf) {
                        relax(freeDp, a * width + b + 1, cur + remain);
                        if (a < na) {
                            int useTime = daTime[a];
                            if (sa[a] != sb[b]) {
                                if (useTime < remain) relax(bRun, ((a + 1) * width + b) * 101 + remain - useTime, cur + useTime);
                                else if (useTime > remain) relax(aRun, (a * width + b + 1) * 101 + useTime - remain, cur + remain);
                                else relax(freeDp, (a + 1) * width + b + 1, cur + remain);
                            } else {
                                relax(aRun, (a * width + b + 1) * 101 + useTime, cur + remain);
                            }
                        }
                    }
                }
            }
        }
        cout << freeDp[na * width + nb] << '\n';
    }
    return 0;
}
