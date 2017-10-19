// Stern-Brocot Tree
// UVa ID: 11350
// Verdict: Accepted
// Submission Date: 2017-10-19
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

    int cases = 0;
    string sequence;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> sequence;

        long long n1 = 0, n2 = 1, n3 = 1;
        long long d1 = 1, d2 = 1, d3 = 0;

        for (auto letter : sequence)
        {
            if (letter == 'L')
            {
                n3 = n2, d3 = d2;
                n2 += n1, d2 += d1;
            }
            else
            {
                n1 = n2, d1 = d2;
                n2 += n3, d2 += d3;
            }
        }

        cout << n2 << '/' << d2 << '\n';
    }

    return 0;
}
