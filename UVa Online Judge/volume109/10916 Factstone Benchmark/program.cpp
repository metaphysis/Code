// Factstone Benchmark
// UVa ID: 10916
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.060s
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

    int year;
    while (cin >> year, year > 0)
    {
        int bits = 4 * pow(2, year / 10 - 196);
        double e = 0;
        int n = 0;
        while (true)
        {
            int next = n + 1;
            double lg = log(next) / log(2);
            if (e + lg <= bits) e += lg, n = next;
            else break;
        }
        cout << n << '\n';
    }

    return 0;
}
