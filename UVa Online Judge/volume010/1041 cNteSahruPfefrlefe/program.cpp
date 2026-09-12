// cNteSahruPfefrlefe
// UVa ID: 1041
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const int maxShuffle = 10;
const int cardNum = 52;

int a[maxShuffle + 1][cardNum];
int b[maxShuffle + 1][cardNum];
int p[cardNum];
int ansShuffle[maxShuffle];
int ansPos[maxShuffle];
int curShuffle[maxShuffle];
int curPos[maxShuffle];
int shuffleNum;
int errorNum;
int bestError;
int caseNum;

int getHeu(int k, int s) {
    int cnt = 0;
    for (int i = 0; i < cardNum; i++)
        if (a[k][b[s][i]] != p[i]) cnt++;
    return (cnt + 1) >> 1;
}

bool compareAnswer() {
    for (int i = 0; i < bestError; i++)
        if (curPos[i] != ansPos[i]) return curPos[i] < ansPos[i];
    return false;
}

bool idaStar(int k = 0, int cnt = 0) {
    if (cnt == errorNum) {
        int step = shuffleNum - k;
        for (int i = 0; i < cardNum; i++)
            if (a[k][b[step][i]] != p[i]) return false;
        return true;
    }
    for (int pos = 0; pos < cardNum - 1; pos++) {
        for (int next = k + 1; cnt + 1 + shuffleNum - next >= errorNum; next++) {
            for (int i = 0; i < cardNum; i++)
                a[next][i] = a[k][b[next - k][i]];
            swap(a[next][pos], a[next][pos + 1]);
            curShuffle[cnt] = next;
            curPos[cnt] = pos;
            if (cnt + getHeu(next, shuffleNum - next) < errorNum && idaStar(next, cnt + 1)) return true;
        }
    }
    return false;
}

void solve() {
    for (int i = 0; i < cardNum; i++) {
        cin >> p[i];
        a[0][i] = i;
    }
    bestError = maxShuffle + 1;
    for (shuffleNum = 1; shuffleNum <= maxShuffle; shuffleNum++) {
        for (errorNum = 0; errorNum <= shuffleNum; errorNum++) {
            if (idaStar()) {
                if (errorNum < bestError || errorNum == bestError && compareAnswer()) {
                    bestError = errorNum;
                    for (int i = 0; i < errorNum; i++) {
                        ansShuffle[i] = curShuffle[i];
                        ansPos[i] = curPos[i];
                    }
                }
                break;
            }
        }
        if (bestError != maxShuffle + 1) break;
    }
    cout << "Case " << ++caseNum << '\n';
    cout << "Number of shuffles = " << shuffleNum << '\n';
    if (bestError == 0)
        cout << "No error in any shuffle\n";
    else
        for (int i = 0; i < bestError; i++)
            cout << "Error in shuffle " << ansShuffle[i] << " at location " << ansPos[i] << '\n';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < cardNum; i++)
        b[0][i] = i;
    for (int i = 1; i <= maxShuffle; i++) {
        for (int j = 0; j < cardNum / 2; j++)
            b[i][j * 2 + 1] = b[i - 1][j];
        for (int j = cardNum / 2; j < cardNum; j++)
            b[i][(j - cardNum / 2) * 2] = b[i - 1][j];
    }
    int testNum;
    cin >> testNum;
    while (testNum--) solve();
    return 0;
}
