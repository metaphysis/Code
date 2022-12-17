// Andy's Shoes
// UVa ID: 11330
// Verdict: Accepted
// Submission Date: 2022-11-22
// UVa Run Time: 0.110s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int rightShoe[10010], color[20010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--)
    {
        int n;
        cin >> n;
        n <<= 1;
        for (int i = 0; i < n; i++)
        {
            cin >> color[i];
            if (i & 1) rightShoe[color[i]] = i;
        }
        int swaps = 0;
        for (int i = 0; i < n; i += 2)
        {
            if (color[i] == color[i + 1]) continue;
            rightShoe[color[i + 1]] = rightShoe[color[i]];
            color[rightShoe[color[i]]] = color[i + 1];
            swaps++;
        }
        cout << swaps << '\n';
    }
    return 0;
}
