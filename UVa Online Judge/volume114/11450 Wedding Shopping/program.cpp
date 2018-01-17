// Wedding Shopping
// UVa ID: 11450
// Verdict: Accepted
// Submission Date: 2018-01-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int M, C, K;
        cin >> M >> C;
        
        vector<int> coins[24];
        for (int i = 1; i <= C; i++)
        {
            cin >> K;
            
            int p;
            for (int j = 1; j <= K; j++)
            {
                cin >> p;
                coins[i].push_back(p);
            }
        }
        
        bool money[24][210];
        memset(money, 0, sizeof(money));
        money[0][0] = true;

        for (int i = 1; i <= C; i++)
            for (auto j : coins[i])
                for (int k = M; k >= 1; k--)
                    money[i][k] = money[i][k] || money[i - 1][k - j];
        bool flag = false;
        for (int i = M; i >= 0; i--)
            if (money[C][i])
            {
                cout << i << '\n';
                flag = true;
                break;
            }
        if (!flag) cout << "no solution\n";
    }

    return 0;
}
