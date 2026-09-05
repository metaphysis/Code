#include <bits/stdc++.h>
using namespace std;

double sel[76][31][31], tr1[76][31], tr2[76][31], dp[76];

void buildTravel(int n, int low, int high, double tr[][31]) {
    memset(tr, 0, sizeof(double) * 76 * 31);
    int cnt = high - low + 1;
    for (int oldCnt = 0; oldCnt <= n; oldCnt++) {
        for (int len = low; len <= high; len++) {
            int playCnt = min(len, n);
            int maxAdd = min(playCnt, n - oldCnt);
            for (int addCnt = 0; addCnt <= maxAdd; addCnt++)
                tr[oldCnt][addCnt] += sel[oldCnt][playCnt][addCnt] / cnt;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        int n, p1, q1, p2, q2;
        cin >> n >> p1 >> q1 >> p2 >> q2;
        cout << "Case " << caseNo << ": ";
        if (q1 == 0 && q2 == 0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        memset(sel, 0, sizeof(sel));
        for (int oldCnt = 0; oldCnt <= n; oldCnt++) {
            sel[oldCnt][0][0] = 1.0;
            for (int stepCnt = 0; stepCnt < 30 && stepCnt < n; stepCnt++) {
                int maxAdd = min(stepCnt, n - oldCnt);
                for (int addCnt = 0; addCnt <= maxAdd; addCnt++) {
                    double cur = sel[oldCnt][stepCnt][addCnt];
                    int remNew = n - oldCnt - addCnt, remOld = oldCnt - (stepCnt - addCnt);
                    double total = remNew + 2.0 * remOld;
                    if (cur == 0.0) continue;
                    if (remNew > 0)
                        sel[oldCnt][stepCnt + 1][addCnt + 1] += cur * remNew / total;
                    if (remOld > 0)
                        sel[oldCnt][stepCnt + 1][addCnt] += cur * 2.0 * remOld / total;
                }
            }
        }
        buildTravel(n, p1, q1, tr1);
        buildTravel(n, p2, q2, tr2);
        dp[n] = 0.0;
        for (int oldCnt = n - 1; oldCnt >= 0; oldCnt--) {
            double day[61] = {};
            int maxA = min(30, n - oldCnt);
            for (int addA = 0; addA <= maxA; addA++) {
                int maxB = min(30, n - oldCnt - addA);
                for (int addB = 0; addB <= maxB; addB++)
                    day[addA + addB] += tr1[oldCnt][addA] * tr2[oldCnt + addA][addB];
            }
            double sum = 1.0;
            int maxAdd = min(60, n - oldCnt);
            for (int addCnt = 1; addCnt <= maxAdd; addCnt++)
                sum += day[addCnt] * dp[oldCnt + addCnt];
            dp[oldCnt] = sum / (1.0 - day[0]);
        }
        cout << fixed << setprecision(10) << dp[0] << '\n';
    }
    return 0;
}
