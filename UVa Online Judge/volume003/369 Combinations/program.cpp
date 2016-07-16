// Combinations
// UVa ID: 369
// Verdict: Accetped
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

vector <int> primes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
    61, 67, 71, 73, 79, 83, 89, 97
};

void getPrimes(int n, map < int, int >& factors)
{
    for (int i = 2; i <= n; i++)
    {
        int t = i;
        while (t > 1)
        {
          for (auto p : primes)
                if (t % p == 0)
                {
                    factors[p]++;
                    t /= p;
                }
        }
    }
}

int main(int argc, char *argv[])
{
    int N, M;
    while (cin >> N >> M, N && M)
    {
        map < int, int >factorsOfN, factorsOfN_M, factorsOfM;
      for (auto p : primes)
            factorsOfN[p] = 0, factorsOfN_M[p] = 0, factorsOfM[p] = 0;

        getPrimes(N, factorsOfN);
        getPrimes(N - M, factorsOfN_M);
        getPrimes(M, factorsOfM);

      for (auto p : factorsOfN_M)
            if (p.second > 0)
                factorsOfN[p.first] -= factorsOfN_M[p.first];

      for (auto p : factorsOfM)
            if (p.second > 0)
                factorsOfN[p.first] -= factorsOfM[p.first];

        int product = 1;
      for (auto p : factorsOfN)
            if (p.second > 0)
                product *= pow(p.first, p.second);

        cout << N << " things taken " << M << " at a time is ";
        cout << product << " exactly." << endl;
    }

    return 0;
}
