// John
// UVa ID: 1566
// Verdict: Accepted
// Submission Date: 2018-02-03
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

    int cases, piles, bitXor, n, ones;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> piles;

        bitXor = ones = 0;
        for (int i = 0; i < piles; i++)
        {
            cin >> n;
            bitXor ^= n;
            if (n == 1) ones++;
        }

        if (ones == piles)
        {
            if (piles & 1) cout << "Brother\n";
            else cout << "John\n";
        }
        else
        {
            if (bitXor) cout << "John\n";
            else cout << "Brother\n";
        }
    }

    return 0;
}
