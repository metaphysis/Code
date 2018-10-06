// Chemical Reaction
// UVa ID: 10604
// Verdict: Accepted
// Submission Date: 2018-10-06
// UVa Run Time: 0.100s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct reaction
{
    int chemical_type, heat_emitted;
} cr[10][10];

map<string, int> dp;

const int INF = 0x7f7f7f7f;

int dfs(string mark)
{
    if (mark.length() == 1) return 0;
    if (dp.find(mark) != dp.end()) return dp[mark];
    int r = INF;
    for (int i = 0; i < mark.length(); i++)
        for (int j = 0; j < mark.length(); j++)
        {
            if (i == j) continue;
            int new_r = cr[mark[i] - '0'][mark[j] - '0'].heat_emitted;
            string next_mark = mark;
            int ii = i, jj = j;
            if (ii > jj) swap(ii, jj);
            next_mark.erase(next_mark.begin() + jj);
            next_mark.erase(next_mark.begin() + ii);
            next_mark.push_back('0' + cr[mark[i] - '0'][mark[j] - '0'].chemical_type);
            sort(next_mark.begin(), next_mark.end());
            new_r += dfs(next_mark);
            r = min(r, new_r);
        }
    return dp[mark] = r;   
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, N, cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> M;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
            {
                cin >> cr[i][j].chemical_type;
                cr[i][j].chemical_type -= 1;
                cin >> cr[i][j].heat_emitted;
            }
        cin >> N;
        string mark;
        for (int i = 0, k; i < N; i++)
        {
            cin >> k;
            mark.push_back('0' + k - 1);
        }
        char separator;
        cin >> separator;

        dp.clear();
        cout << dfs(mark) << '\n';
    }

    return 0;
}
