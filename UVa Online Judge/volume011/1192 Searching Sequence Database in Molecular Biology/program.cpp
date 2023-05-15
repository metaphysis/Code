// Searching Sequence Database in Molecular Biology
// UVa ID: 1192
// Verdict: Accepted
// Submission Date: 2023-05-15
// UVa Run Time: 0.600s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

string s, t;
int dp[1010][1010], ns, nt;
vector<string> ss;
vector<int> c;

int dfs(int i, int j) {
    if (i == ns || j == nt) return -7 * (ns + nt - i - j);
    if (dp[i][j] != -INF) return dp[i][j];
    int c = (s[i] == t[j] ? 5 : -4) + dfs(i + 1, j + 1);
    c = max(c, -7 + dfs(i, j + 1));
    c = max(c, -7 + dfs(i + 1, j));
    return dp[i][j] = c;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> s >> s;
    cout << "The query sequence is:\n";
    cout << s << '\n';
    cout << '\n';
    ns = s.length();

    while (cin >> t) {
        cin >> t;
        ss.push_back(t);
        nt = t.length();
        for (int i = 0; i < ns; i++)
            for (int j = 0; j < nt; j++)
                dp[i][j] = -INF;
        c.push_back(dfs(0, 0));
    }

    cout << "The most similar sequences are:\n";
    cout << '\n';
    int mc = *max_element(c.begin(), c.end());
    int printed = 0;
    for (int i = 0; i < c.size(); i++)
        if (c[i] == mc) {
            if (printed) cout << '\n';
            cout << ss[i] << '\n';
            cout << "The similarity score is: " << mc << '\n';
            printed = 1;
        }

    return 0;
}
