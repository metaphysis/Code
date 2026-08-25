#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    while (test--) {
        int n, k;
        cin >> n >> k;
        vector<int> pos(n + 1), wei(n + 1);
        vector<long long> preW(n + 1), preP(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> pos[i] >> wei[i];
            preW[i] = preW[i - 1] + wei[i];
            preP[i] = preP[i - 1] + 1LL * pos[i] * wei[i];
        }
        int truck = (n + k - 1) / k;
        int miss = truck * k - n;
        int step = k + 1;
        vector<int> medTab((n + 1) * step);
        for (int st = 1; st <= n; st++) {
            int med = st;
            int endPos = min(n, st + k - 1);
            for (int ed = st; ed <= endPos; ed++) {
                long long totalW = preW[ed] - preW[st - 1];
                while (med < ed && 2 * (preW[med] - preW[st - 1]) < totalW)
                    med++;
                int len = ed - st + 1;
                medTab[(st - 1) * step + len] = med;
            }
        }
        const long long inf = (1LL << 62);
        vector<long long> oldDp(miss + 1, inf), newDp(miss + 1, inf);
        oldDp[0] = 0;
        for (int group = 1; group <= truck; group++) {
            fill(newDp.begin(), newDp.end(), inf);
            for (int curMiss = 0; curMiss <= miss; curMiss++) {
                int endPos = group * k - curMiss;
                for (int preMiss = 0; preMiss <= curMiss; preMiss++) {
                    if (oldDp[preMiss] == inf)
                        continue;
                    int st = (group - 1) * k - preMiss + 1;
                    int len = endPos - st + 1;
                    int med = medTab[(st - 1) * step + len];
                    long long leftW = preW[med - 1] - preW[st - 1];
                    long long leftP = preP[med - 1] - preP[st - 1];
                    long long rightW = preW[endPos] - preW[med];
                    long long rightP = preP[endPos] - preP[med];
                    long long cost = 1LL * pos[med] * leftW - leftP + rightP - 1LL * pos[med] * rightW;
                    newDp[curMiss] = min(newDp[curMiss], oldDp[preMiss] + cost);
                }
            }
            oldDp.swap(newDp);
        }
        cout << truck << ' ' << oldDp[miss] << '\n';
    }
    return 0;
}
