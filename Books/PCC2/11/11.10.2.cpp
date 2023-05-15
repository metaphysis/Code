#include <bits/stdc++.h>

using namespace std;

const int IMINUS_JMINUS = 1, IMINUS = 2, JMINUS = 3;

struct block { int n, way; };

void lcs(string &s, string &t) {
    int ns = s.length(), nt = t.length();
    block dp[ns + 1][nt + 1] = {};
    for (int i = 1; i <= ns; i++)
        for (int j = 1; j <= nt; j++)
            if (s[i - 1] == t[j - 1]) {
                if (dp[i][j].n < dp[i - 1][j - 1].n + 1) {
                    dp[i][j].n = dp[i - 1][j - 1].n + 1;
                    dp[i][j].way = IMINUS_JMINUS;
                }
            } else {
                if (dp[i][j].n < dp[i - 1][j].n)
                    dp[i][j].n = dp[i - 1][j].n, dp[i][j].way = IMINUS;
                if (dp[i][j].n < dp[i][j - 1].n)
                    dp[i][j].n = dp[i][j - 1].n, dp[i][j].way = JMINUS;
            }
    string r;
    int endi = ns, endj = nt;
    while (dp[endi][endj].way) {
        if (dp[endi][endj].way == IMINUS_JMINUS) {
            r.push_back(s[endi - 1]);
            endi -= 1, endj -= 1;
        } else {
            if (dp[endi][endj].way == IMINUS) endi -= 1;
            else endj -= 1;
        }
    }
    reverse(r.begin(), r.end());
    cout << dp[ns][nt] << ' ' << r << '\n';
}

int main(int argc, char *argv[]) {
    string s, t;
    while (cin >> s >> t) lcs(s, t);
    return 0;
}
