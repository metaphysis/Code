// Jackpot
// UVa ID: 561
// Verdict: TLE
// Submission Date: 2017-05-12
// UVa Run Time: 3.000s
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

    int cases = 0, x, y, z;
    string wheel1, wheel2, wheel3;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> x >> y >> z;
        cin >> wheel1 >> wheel2 >> wheel3;

        wheel1 += wheel1[0], wheel1 += wheel1[1];
        wheel2 += wheel2[0], wheel2 += wheel2[1];
        wheel3 += wheel3[0], wheel3 += wheel3[1];
        
        int coins = 0;
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                for (int k = 0; k < z; k++)
                {
                    if (wheel1[i] == wheel2[j] && wheel2[j] == wheel3[k]) coins += 5;
                    if (wheel1[i + 1] == wheel2[j + 1] && wheel2[j + 1] == wheel3[k + 1]) coins += 10;
                    if (wheel1[i + 2] == wheel2[j + 2] && wheel2[j + 2] == wheel3[k + 2]) coins += 5;
                    if (wheel1[i] == wheel2[j + 1] && wheel2[j + 1] == wheel3[k + 2]) coins += 7;
                    if (wheel1[i + 2] == wheel2[j + 1] && wheel2[j + 1] == wheel3[k]) coins += 7;
                }

        cout << fixed << setprecision(4) << (double)(coins) / (x * y * z) << '\n';
    }

    return 0;
}
