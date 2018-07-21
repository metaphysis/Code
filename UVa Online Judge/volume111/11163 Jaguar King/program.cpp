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
int best, maxDepth, minDepth;

int getTotalScore()
{
    int fn = 0;
    for (int i = 0; i < n; i++)
        fn += jumps[tiger[i]][i];
    return fn;
}

void dfs(int hn, int gn, int preKing, int nowKing)
{
    if (hn == 0)
    {
        best = min(best, gn);
        return;
    }
    if (hn + gn >= best) return;

    int nextHn, nextKing, mod = (nowKing + 1) % 4;
    for (int k = 0; k < 4; k++)
    {
        nextKing = nowKing + offset[mod][k];
        if (nextKing < 0 || nextKing >= n || nextKing == preKing) continue;
        nextHn = hn - (jumps[tiger[nowKing]][nowKing] + jumps[tiger[nextKing]][nextKing]);
        //cout << "Before Exchanged nextHn = " << nextHn << '\n';
        // Jump
        swap(tiger[nowKing], tiger[nextKing]);
        nextHn += (jumps[tiger[nowKing]][nowKing] + jumps[tiger[nextKing]][nextKing]);
        //print();
        //cout << "After Changed nextHn = " << nextHn << '\n';
        if (nextHn + gn < min(best, maxDepth))
            dfs(nextHn, gn + 1, nowKing, nextKing);
        else
            minDepth = min(minDepth, nextHn + gn);
        // Restore
        swap(tiger[nowKing], tiger[nextKing]);
    }
}

void idaStar(int king)
{
    maxDepth = 0;
    minDepth = getTotalScore();

    while (true)
    {
        maxDepth = maxDepth < minDepth ? minDepth : maxDepth + 1;
        minDepth = INT_MAX;

        best = 0x3f3f3f3f;

        dfs(getTotalScore(), 0, -10, king);

        if (best != 0x3f3f3f3f)
        {
            cout << best << '\n';
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
