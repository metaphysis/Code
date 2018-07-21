// Jaguar King
// UVa ID: 11163
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int offset[4][4] = {
    {-4, -3, -1, 4},
    {-4, 1, 3, 4},
    {-4, -1, 1, 4},
    {-4, -1, 1, 4}
};

int tiger[50], jumps[45][45] = {}, n;
int sorted, maxDepth;

int getTotalScore()
{
    int fn = 0;
    for (int i = 0; i < n; i++)
        fn += jumps[tiger[i]][i];
    return fn;
}

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
    return a.second < b.second;
}

void dfs(int hn, int gn, int preKing, int nowKing)
{
    if (hn + gn > maxDepth) return;
    if (hn == 0)
    {
        sorted = 1;
        maxDepth = gn;
        return;
    }
    int mod = (nowKing + 1) % 4, cnt = 0;
    pair<int, int> saved[4];
    for (int k = 0; k < 4; k++)
    {
        int nextKing = nowKing + offset[mod][k];
        if (nextKing < 0 || nextKing >= n || nextKing == preKing) continue;
        int nextHn = hn;
        nextHn -= (jumps[tiger[nowKing]][nowKing] + jumps[tiger[nextKing]][nextKing]);
        nextHn += (jumps[tiger[nextKing]][nowKing] + jumps[tiger[nowKing]][nextKing]);
        saved[cnt++] = make_pair(nextKing, nextHn);
    }
    sort(saved, saved + cnt, cmp);
    for (int k = 0; k < cnt; k++)
    {
        swap(tiger[nowKing], tiger[saved[k].first]);
        dfs(saved[k].second, gn + 1, nowKing, saved[k].first);
        if (sorted) return;
        swap(tiger[nowKing], tiger[saved[k].first]);
    }
}

void idaStar(int king)
{
    maxDepth = 0;
    while (true)
    {
        maxDepth++;
        sorted = 0;
        dfs(getTotalScore(), 0, -10, king);
        if (maxDepth >= 35)
        {
            sorted = 1;
            maxDepth = -1;
        }
        if (sorted)
        {
            cout << maxDepth << '\n';
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i <= 40; i++)
        for (int j = 0; j <= 40; j++)
            jumps[i][j] = (abs(i - (j + 1)) + 3) / 4;

    int cases = 0, king;
    while (cin >> n, n > 0)
    {
        cout << "Set " << ++cases << ":\n";

        for (int i = 0; i < n; i++)
        {
            cin >> tiger[i];
            if (tiger[i] == 1) king = i;
        }

        idaStar(king);
    }

    return 0;
}
