// A Gentlemen's Agreement
// UVa ID: 11065
// Verdict: Accepted
// Submission Date: 2018-07-07
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int numberOfI, numberOfR, cntOfMVIS, valueOfIN;
long long masks[64], allOnes;

void dfs(int depth, int ones, long long forbidden)
{
    if (forbidden == allOnes)
    {
        cntOfMVIS++;
        valueOfIN = max(valueOfIN, ones);
        return;
    }

    for (int i = depth; i < numberOfI; i++)
        if (!(forbidden & (1LL << i)))
            dfs(i + 1, ones + 1, forbidden | masks[i] | (1LL << i));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> numberOfI >> numberOfR;
        memset(masks, 0, sizeof(masks));
        int from, to;
        for (int i = 0; i < numberOfR; i++)
        {
            cin >> from >> to;
            masks[from] |= (1LL << to);
            masks[to] |= (1LL << from);
        }

        allOnes = (1LL << numberOfI) - 1;
        cntOfMVIS = valueOfIN = 0;
        dfs(0, 0, 0);
        cout << cntOfMVIS << '\n' << valueOfIN << '\n';
    }

    return 0;
}
