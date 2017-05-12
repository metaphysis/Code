// Jackpot
// UVa ID: 561
// Verdict: Accepted
// Submission Date: 2017-05-12
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

    int cases = 0, x, y, z;
    string wheel1, wheel2, wheel3;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> x >> y >> z;
        cin >> wheel1 >> wheel2 >> wheel3;

        int count1[26] = {0}, count2[26] = {0}, count3[26] = {0};
        
        for (int i = 0; i < x; i++)
            count1[wheel1[i] - 'A']++;
        for (int i = 0; i < y; i++)
            count2[wheel2[i] - 'A']++;
        for (int i = 0; i < z; i++)
            count3[wheel3[i] - 'A']++;
        
        double average = 0.0;
        for (int i = 0; i < 26; i++)
        {
            double rate = 1.0;
            rate *= (double)(count1[i]) / (double)(x);
            rate *= (double)(count2[i]) / (double)(y);
            rate *= (double)(count3[i]) / (double)(z);
            average += rate * 34.0;
        }

        cout << fixed << setprecision(4) << average << '\n';
    }

    return 0;
}
