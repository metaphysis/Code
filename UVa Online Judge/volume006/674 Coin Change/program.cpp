// Coin Change
// UVa ID: 674
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int coins[6] = {0, 1, 5, 10, 25, 50};
    long long int ways[6][7500];

    memset(ways, 0, sizeof(ways));
    ways[0][0] = 1;
    
    for (int i = 1; i <= 5; i++)
        for (int j = 0; j <= 7489; j++)
        {
            ways[i][j] = ways[i - 1][j];
            if (j - coins[i] >= 0)
                ways[i][j] += ways[i][j - coins[i]];
        }
    
    int cents;   
    while (cin >> cents)
        cout << ways[5][cents] << '\n';
    
	return 0;
}
