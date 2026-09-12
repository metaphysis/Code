// Blanket
// UVa ID: 12874
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.160s

#include <bits/stdc++.h>
using namespace std;

const int periodLen = 720720;

void addPart(int len, int good[17][17], long long result[]) {
    int state[17], cover;
    for (int b = 1; b <= 16; b++) state[b] = 0;
    for (int x = 0; x < len; x++) {
        cover = 0;
        for (int b = 1; b <= 16; b++) cover += good[b][state[b]];
        result[cover]++;
        for (int b = 1; b <= 16; b++) {
            state[b]++;
            if (state[b] == b) state[b] = 0;
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    int freq[17][17], good[17][17];
    memset(freq, 0, sizeof(freq));
    memset(good, 0, sizeof(good));
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        freq[b][a]++;
    }
    for (int b = 1; b <= 16; b++)
        for (int r = 0; r < b; r++)
            for (int a = r + 1; a <= b; a++)
                good[b][r] += freq[b][a];
    long long answer[n + 1];
    memset(answer, 0, sizeof(answer));
    long long quotient = m / periodLen;
    int remainder = m % periodLen;
    if (quotient == 0) {
        addPart(m, good, answer);
    } else {
        long long cycleResult[n + 1], remainResult[n + 1];
        memset(cycleResult, 0, sizeof(cycleResult));
        memset(remainResult, 0, sizeof(remainResult));
        addPart(periodLen, good, cycleResult);
        addPart(remainder, good, remainResult);
        for (int i = 0; i <= n; i++) answer[i] = cycleResult[i] * quotient + remainResult[i];
    }
    for (int i = 0; i <= n; i++) cout << answer[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) solve();
    return 0;
}
