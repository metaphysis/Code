// The Win-stay and Lose-shift Strategy 
// UVa ID: 12790
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

int charToInt(char c) {
    if (c == 'R') return 0;
    if (c == 'P') return 1;
    return 2;
}

int getScore(int a, int b) {
    if (a == b) return 0;
    if ((a == 0 && b == 2) || (a == 1 && b == 0) || (a == 2 && b == 1))
        return 1;
    return -1;
}

int beatHand(int x) {
    return (x + 1) % 3;
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        char aStr[10005], bStr[10005];
        scanf("%s %s", aStr, bStr);
        int pR, pP, pS;
        scanf("%d %d %d", &pR, &pP, &pS);
        int n = strlen(aStr);
        int x = 0;
        for (int i = 0; i < n; ++i) {
            int ai = charToInt(aStr[i]);
            int bi = charToInt(bStr[i]);
            x += getScore(ai, bi);
        }
        double prob[3] = {pR / 100.0, pP / 100.0, pS / 100.0};
        double dp[3][3] = {};
        double y = 0.0;
        int b0 = charToInt(bStr[0]);
        for (int g = 0; g < 3; ++g) {
            double pr = prob[g];
            int s = getScore(g, b0);
            y += pr * s;
            int res = (s > 0 ? 0 : (s < 0 ? 1 : 2));
            dp[g][res] += pr;
        }
        for (int i = 1; i < n; ++i) {
            double newDp[3][3] = {};
            int bPrev = charToInt(bStr[i - 1]);
            int bCur = charToInt(bStr[i]);
            for (int prevA = 0; prevA < 3; ++prevA) {
                for (int prevRes = 0; prevRes < 3; ++prevRes) {
                    double pr = dp[prevA][prevRes];
                    if (pr == 0.0) continue;
                    if (prevRes == 2) {
                        for (int g = 0; g < 3; ++g) {
                            double prg = pr * prob[g];
                            int s = getScore(g, bCur);
                            y += prg * s;
                            int res = (s > 0 ? 0 : (s < 0 ? 1 : 2));
                            newDp[g][res] += prg;
                        }
                    } else if (prevRes == 0) {
                        int cur = beatHand(prevA);
                        int s = getScore(cur, bCur);
                        y += pr * s;
                        int res = (s > 0 ? 0 : (s < 0 ? 1 : 2));
                        newDp[cur][res] += pr;
                    } else {
                        int cur = beatHand(bPrev);
                        int s = getScore(cur, bCur);
                        y += pr * s;
                        int res = (s > 0 ? 0 : (s < 0 ? 1 : 2));
                        newDp[cur][res] += pr;
                    }
                }
            }
            for (int a = 0; a < 3; ++a)
                for (int r = 0; r < 3; ++r)
                    dp[a][r] = newDp[a][r];
        }
        bool better = (y > x);
        printf("%d %.4f %c\n", x, y, better ? 'Y' : 'N');
    }
    return 0;
}
