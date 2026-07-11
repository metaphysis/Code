// Crossword
// UVa ID: 768
// Verdict: Accepted
// Submission Date: 2026-07-11
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int L, N, minL, head[32], used[1024];
int line[64], best[64];
string words[1024];

void dfs(int last, int now) {
    int better = 1;
    for (int i = 0; i < L; i++) {
        if (line[i] < best[i]) break;
        if (line[i] > best[i]) { better = 0; break; }
    }
    if (!better) return;
    if (now < L && L - now < minL) return;
    if (last == L && now == L) {
        for (int i = 0; i < L; ++i) best[i] = line[i];
        return;
    }
    int start = 0, end = N;
    if (last) {
        int c = line[last] - 'a';
        start = head[c];
        end = (c == 25 ? N : head[c + 1]);
    }
    for (int id = start; id < end; id++) {
        if (used[id]) continue;
        string& w = words[id];
        int step = w.size();
        if (last + step > L) continue;
        if (last + step == now && now != L) continue;
        int ok = 1;
        for (int i = 0; i < min(step, now - last); i++)
            if (line[last + i] != w[i]) { ok = 0; break; }
        if (!ok) continue;
        for (int i = 0; i < step; i++) line[last + i] = w[i];
        used[id] = 1;
        dfs(min(last + step, now), max(last + step, now));
        used[id] = 0;
        for (int i = now; i < last + step; i++) line[i] = 0;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> L) {
        cin >> N;
        minL = 32;
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
            minL = min(minL, (int)words[i].size());
        }
        for (int i = 0; i < 26; ++i) {
            string s(1, char('a' + i));
            head[i] = lower_bound(words, words + N, s) - words;
        }
        memset(line, 0, sizeof(line));
        memset(used, 0, sizeof(used));
        for (int i = 0; i < 64; ++i) best[i] = 128;
        dfs(0, 0);
        if (best[0] == 128) cout << "NO SOLUTION\n";
        else {
            for (int i = 0; i < L; ++i) cout << (char)best[i];
            cout << '\n';
        }
    }
    return 0;
}
