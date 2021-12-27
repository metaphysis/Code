// A Pile of Boxes
// UVa ID: 946
// Verdict: Accepted
// Submission Date: 2021-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int lengthOfBox[128], pile[128][128], cntOfPile[128], sizeOfPile[128];

bool fit(int pileId, int boxId)
{
    for (int i = 0; i < cntOfPile[pileId]; i++)
    {
        if (lengthOfBox[boxId] > lengthOfBox[pile[pileId][i]]) continue;
        if (fit(pile[pileId][i], boxId)) return true;
    }
    if (pileId && sizeOfPile[pileId] + lengthOfBox[boxId] <= lengthOfBox[pileId])
    {
        pile[pileId][cntOfPile[pileId]++] = boxId;
        sizeOfPile[pileId] += lengthOfBox[boxId];
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        memset(cntOfPile, 0, sizeof cntOfPile);
        memset(sizeOfPile, 0, sizeof sizeOfPile);
        for (int i = 1; i <= n; i++)
        {
            cin >> lengthOfBox[i];
            if (!fit(0, i)) pile[0][cntOfPile[0]++] = i;
        }
        int height = 0;
        for (int i = 0; i < cntOfPile[0]; i++) height += lengthOfBox[pile[0][i]];
        cout << height << '\n';
    }
    return 0;
}
