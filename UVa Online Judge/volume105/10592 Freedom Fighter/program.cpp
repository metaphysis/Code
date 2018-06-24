// Freedom Fighter
// UVa ID: 10592
// Verdict: Accepted
// Submission Date: 2018-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, zeros = 0, ones = 0;
vector<pair<int, int>> B, P;
char grid[56][56];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs1(int i, int j)
{
    if (grid[i][j] == '.' || grid[i][j] == '0' || grid[i][j] == '1') return;
    if (grid[i][j] == '*') grid[i][j] = '.';
    if (grid[i][j] == 'B') grid[i][j] = '0', B.push_back(make_pair(i, j));
    if (grid[i][j] == 'P') grid[i][j] = '1', P.push_back(make_pair(i, j));
    for (int k = 0; k < 4; k++)
    {
        int ii = i + offset[k][0], jj = j + offset[k][1];
        if (ii >= 0 && ii < n && jj >= 0 && jj < n)
            dfs1(ii, jj);
    }
}

void dfs2(int i, int j)
{
    if (grid[i][j] == '.') return;
    if (grid[i][j] == '0') grid[i][j] = '.', zeros++;
    if (grid[i][j] == '1') grid[i][j] = '.', ones++;
    for (int k = 0; k < 4; k++)
    {
        int ii = i + offset[k][0], jj = j + offset[k][1];
        if (ii >= 0 && ii < n && jj >= 0 && jj < n)
            dfs2(ii, jj);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];

        int tF = 0, sectors = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '*' || grid[i][j] == 'B' || grid[i][j] == 'P')
                {
                    int tB = 0, tP = 0;
                    B.clear(), P.clear();
                    
                    dfs1(i, j);

                    if (B.size() > 0 || P.size() > 0)
                    {
                        for (int k = 0; k < B.size(); k++)
                        {
                            if (grid[B[k].first][B[k].second] == '.') continue;
                            zeros = ones = 0;
                            dfs2(B[k].first, B[k].second);
                            tB += 1;
                            if (zeros && ones) tF += 2, tP += 1;
                        }
                        for (int k = 0; k < P.size(); k++)
                        {
                            if (grid[P[k].first][P[k].second] == '.') continue;
                            zeros = ones = 0;
                            dfs2(P[k].first, P[k].second);
                            tP += 1;
                            if (zeros && ones) tF += 2, tB += 1;
                        }
                    }
                    cout << "Sector #" << ++sectors << ": ";
                    cout << "contain " << tB << " freedom fighter group(s) & " << tP << " enemy group(s)\n";
                }
        }
        cout << "Total " << tF << " group(s) are in fighting position.\n";
        cout << '\n';
    }

    return 0;
}
