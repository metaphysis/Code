// Kick the Ball
// UVa ID: 12828
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

double prob[10], dp[11][6][6];
int guessA, guessB;

bool isEnd(int k, int a, int b) {
    int cntA = (k + 1) / 2, cntB = k / 2;
    int remA = 5 - cntA, remB = 5 - cntB;
    if (a - b > remB) return true;
    if (b - a > remA) return true;
    if (k == 10) return true;
    return false;
}

double solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1.0;
    double ans = 0;
    for (int k = 0; k < 10; k++) {
        for (int a = 0; a <= 5; a++) {
            for (int b = 0; b <= 5; b++) {
                if (dp[k][a][b] == 0) continue;
                double cur = dp[k][a][b];
                double p = k % 2 == 0 ? prob[k / 2] : prob[5 + k / 2];
                int goalA = a, goalB = b;
                if (k % 2 == 0) goalA++;
                else goalB++;
                if (isEnd(k + 1, goalA, goalB)) {
                    if (goalA == guessA && goalB == guessB) ans += cur * p;
                } else {
                    dp[k + 1][goalA][goalB] += cur * p;
                }
                if (isEnd(k + 1, a, b)) {
                    if (a == guessA && b == guessB) ans += cur * (1.0 - p);
                } else {
                    dp[k + 1][a][b] += cur * (1.0 - p);
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNum = 0;
    while (cin >> prob[0]) {
        for (int i = 1; i < 10; i++) cin >> prob[i];
        string guess;
        cin >> guess;
        int pos = guess.find('-');
        guessA = stoi(guess.substr(0, pos));
        guessB = stoi(guess.substr(pos + 1));
        cout << "Case " << ++caseNum << ": " << fixed << setprecision(2) << solve() * 100.0 << "%\n";
    }
    return 0;
}
