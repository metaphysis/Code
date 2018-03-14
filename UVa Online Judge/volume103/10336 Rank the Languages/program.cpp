// Rank the Languages
// UVa ID: 10336
// Verdict: Accepted
// Submission Date: 2018-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[110][110], C, nexti, nextj;
int H, W;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct language
{
    char letter;
    int number;
    bool operator<(const language &l) const
    {
        if (number != l.number) return number > l.number;
        return letter < l.letter;
    }
};

void dfs(int i, int j, char old, char replaced)
{
    grid[i][j] = replaced;
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < H && nextj >= 0 && nextj < W)
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> H >> W;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> grid[i][j];

        map<char, int> cnt;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] != '.')
                {
                    cnt[grid[i][j]]++;
                    dfs(i, j, grid[i][j], '.');
                }

        vector<language> result;
        for (auto p : cnt)
            result.push_back(language{p.first, p.second});
        sort(result.begin(), result.end());
        cout << "World #" << c << '\n';
        for (auto r : result)
            cout << r.letter << ": " << r.number << '\n';
    }

    return 0;
}
