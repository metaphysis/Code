// Simple Adjacency Maximization
// UVa ID: 11532
// Verdict: Accepted
// Submission Date: 2018-01-24
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

    int cases, P, Q;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> P >> Q;
        bitset<64> B(0);
        if (P / 2 < Q)
        {
            for (int i = 0, b = 0; b < P; i += 3)
            {
                B.set(i, 1);
                if (++b == P) break;
                B.set(i + 2, 1);
                if (++b == P) break;
            }
        }
        else
        {
            for (int i = 0; i < (P + Q); i++)
                B.set(i, 1);
            for (int i = (P + Q - 2), b = 0; b < Q; i -= 3)
            {
                B.set(i, 0);
                if (++b == Q) break;
            }
        }
        cout << B.to_ullong() << '\n';
    }

    return 0;
}
