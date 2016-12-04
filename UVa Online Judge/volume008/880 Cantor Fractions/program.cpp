// Cantor Fractions
// UVa ID: 880
// Verdict: Accepted
// Submission Date: 2016-12-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long n;
    while (cin >> n)
    {
        long long i = sqrt(2 * n);
        for (long long j = i - 1; j <= i + 1; j++)
        {
            if (j * (j + 1) >= 2 * n)
            {
                long long remainder = j * (j + 1) / 2 - n;
                cout << (1 + remainder) << '/' << (j - remainder) << '\n';
                break;
            }
        }
    }
    
	return 0;
}
