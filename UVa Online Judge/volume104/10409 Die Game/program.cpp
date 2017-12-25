// Die Game
// UVa ID: 10409
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

    int rotate[4][6] = {
        //{5, 1, 3, 2, 6, 4},
        {4, 0, 2, 1, 3, 5},
        //{4, 2, 1, 3, 5, 6},
        {5, 1, 0, 2, 4, 3},
        //{2, 6, 3, 5, 1, 4},
        {1, 3, 2, 4, 0, 5},
        //{3, 2, 6, 4, 5, 1}
        {2, 1, 3, 5, 4, 0},
    };

    int n;
    while (cin >> n, n > 0)
    {
        string command;
        int dice1[6] = {1, 2, 3, 6, 5, 4}, dice2[6];
        for (int i = 1; i <= n; i++)
        {
            cin >> command;
            int d = 0;
            switch (command.front())
            {
                case 'n': d = 0; break;
                case 'w': d = 1; break;
                case 's': d = 2; break;
                case 'e': d = 3; break;
            }
            for (int i = 0; i < 6; i++) dice2[i] = dice1[rotate[d][i]];
            copy(dice2, dice2 + 6, dice1);
        }
        cout << dice1[0] << '\n';
    }

    return 0;
}
