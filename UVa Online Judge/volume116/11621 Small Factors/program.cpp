// Small Factors
// UVa ID: 11621
// Verdict: Accepted
// Submission Date: 2017-11-30
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

typedef long long int BigNumber;

int main(int argc, char *argv[])
{
    BigNumber factors[2] = {2, 3}, T = (1LL << 31), N, S[1000], C = 0;
    set<BigNumber> uglyNumbers;
    priority_queue<BigNumber, vector<BigNumber>, greater<BigNumber>> q;
    q.push(1);

    while (true)
    {
        do
        {
            N = q.top(); q.pop();
        }
        while (uglyNumbers.find(N) != uglyNumbers.end());

        uglyNumbers.insert(N);
        S[C++] = N;
        for (int i = 0; i < 2; i++)
        {
            BigNumber next = N * factors[i];
            if (uglyNumbers.find(next) == uglyNumbers.end()) q.push(next);
        }
        if (N > T) break;
    }

    while (cin >> N, N > 0)
    {
        for (int i = 0; i < C; i++)
            if (S[i] >= N)
            {
                cout << S[i] << '\n';
                break;
            }
    }

    return 0;
}
