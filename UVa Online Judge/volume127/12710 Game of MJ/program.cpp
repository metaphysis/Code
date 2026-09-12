// Game of MJ
// UVa ID: 12710
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string solve() {
    int displayCount;
    cin >> displayCount;
    ll zeroCnt = 0, oneCnt = 0, twoCnt = 0;
    for (int i = 0; i < displayCount; ++i) {
        ll len, base;
        cin >> len >> base;
        ll digitCnt = len - 1;
        ll pressCnt = base - 1;
        if (base % 3 == 0) {
            zeroCnt += digitCnt * pressCnt;
        } else if (base % 3 == 1) {
            oneCnt += digitCnt * pressCnt;
        } else {
            twoCnt += (digitCnt + 1) / 2 * pressCnt;
            oneCnt += digitCnt / 2 * pressCnt;
        }
    }
    if (oneCnt + twoCnt == 0 && zeroCnt > 0) return "J";
    if (oneCnt + twoCnt <= 2 && (oneCnt == 0 || twoCnt == 0)) return "Draw";
    if ((oneCnt == 0 || twoCnt == 0) && zeroCnt % 2 == 0) return "J";
    if ((oneCnt == 0 || twoCnt == 0) && zeroCnt % 2 == 1) return "M";
    if (zeroCnt % 2 == 0) return "M";
    if (oneCnt == twoCnt) return "J";
    if (abs(oneCnt - twoCnt) <= 2) return "Draw";
    return "M";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cout << "Case " << caseId << ": " << solve() << '\n';
    }
    return 0;
}
