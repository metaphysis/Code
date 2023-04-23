// Lovely Hint
// UVa ID: 11569
// Verdict: Accepted
// Submission Date: 2023-04-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> g[32];
int in[26], L[26], C[26];

pair<int, int> dfs(int u) {
    int r1 = 0, r2 = g[u].size() ? 0 : 1;
    for (auto v : g[u]) {
        pair<int, int> pr = dfs(v);
        if (pr.first > r1) {
            r1 = pr.first;
            r2 = pr.second;
        } else if (pr.first == r1) {
            r2 += pr.second;
        }
    }
    return make_pair(1 + r1, r2);
}

void solve(string s) {
    memset(in, 0, sizeof in);
    for (int i = 0; i < 26; i++) g[i].clear();
    for (int i = 0; i < s.length(); i++)
        for (int j = i + 1; j < s.length(); j++)
            if (5 * (s[i] - 'A' + 1) <= 4 * (s[j] - 'A' + 1)) {
                g[i].push_back(j);
                in[j]++;
            }
    memset(L, 0, sizeof L);
    for (int i = 0; i < s.length(); i++)
        if (!in[i]) {
            pair<int, int> pr = dfs(i);
            L[i] = pr.first, C[i] = pr.second;
        }
    int maxL = *max_element(L, L + 26);
    cout << maxL;
    int T = 0;
    for (int i = 0; i < s.length(); i++)
        if (L[i] == maxL)
            T += C[i];
    cout << ' ' << T << '\n';        
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cin.ignore(256, '\n');
    string line;
    for (int cs = 1; cs <= T; cs++) {
        getline(cin, line);
        sort(line.begin(), line.end());
        string s;
        for (auto c : line)
            if (isalpha(c)) {
                if (s.length() && c == s.back()) continue;
                s += c;
            }
        solve(s);
    }
    return 0;
}
