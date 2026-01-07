// Candles
// UVa ID: 12368
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.140s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool canFormWithMask[1024][110];

int cnt[10];
void add(int mask, int age, string s) {
    memset(cnt, 0, sizeof cnt);
    bool valid = true;
    for (auto c : s) {
        if (cnt[c - '0']) {
            valid = false;
            break;
        }
        cnt[c - '0']++;
    }
    if (valid) {
        for (int i = 0; i < 10; i++)
            if (cnt[i] && !(mask & (1 << i))) {
                valid = false;
                break;
            }
    }
    canFormWithMask[mask][age] |= valid;
}

void initialize() {
    for (int mask = 1; mask < 1024; mask++) {
        for (int age = 1; age <= 100; age++) {
            add(mask, age, to_string(age));
            if (canFormWithMask[mask][age]) continue;
            for (int x = 1; x <= age / 2; x++) {
                add(mask, age, to_string(x) + to_string(age - x));
                if (canFormWithMask[mask][age]) break;
            }
        }
    }
}

int main() {
    initialize();
    int caseNum = 1;
    int n;
    while (cin >> n && n) {
        vector<int> ages(n);
        for (int i = 0; i < n; i++) cin >> ages[i];
        int minCount = 11, bestMask = 0;
        for (int mask = 1; mask < 1024; mask++) {
            int cnt = __builtin_popcount(mask);
            if (cnt > minCount) continue;
            bool ok = true;
            for (int age : ages)
                if (!canFormWithMask[mask][age]) {
                    ok = false;
                    break;
                }
            if (ok) {
                if (cnt < minCount || (cnt == minCount && mask < bestMask)) {
                    minCount = cnt;
                    bestMask = mask;
                }
            }
        }
        string result;
        for (int d = 9; d >= 0; d--)
            if (bestMask & (1 << d))
                result += char('0' + d);
        cout << "Case " << caseNum++ << ": " << result << '\n';
    }
    return 0;
}
