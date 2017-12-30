// Credit Check
// UVa ID: 11743
// Verdict: Accepted
// Submission Date: 2017-12-30
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

    int cases;
    string number[4];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 4; i++)
            cin >> number[i];
        int total = 0;
        for (int i = 0; i < 4; i++)
        {
            total += (number[i][1] - '0' + number[i][3] - '0');
            int k1 = 2 * (number[i][0] - '0');
            int k2 = 2 * (number[i][2] - '0');
            if (k1 >= 10) total += 1;
            total += k1 % 10;
            if (k2 >= 10) total += 1;
            total += k2 % 10;
        }
        if (total % 10 != 0) cout << "Invalid\n";
        else cout << "Valid\n";
    }
    return 0;
}
