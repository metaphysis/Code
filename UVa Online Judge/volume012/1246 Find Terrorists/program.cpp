// Find Terrorists
// UVa ID: 1246
// Verdict: Accepted
// Submission Date: 2018-03-10
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

    int primes[10001] = {0}, cnt = 0;
    for (int i = 2; i < 10001; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < 10001; j += i)
                primes[j] = 1;
        }
    
    int number[10001] = {0};
    for (int i = 0; i < cnt; i++)
    {
        int p = primes[i];
        for (int j = 0; j < cnt; j++)
        {
            int e = pow(p, primes[j] - 1);
            if (e > 10000) break;
            number[e] = 1;
        }
    }
    
    int cases, L, H;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> L >> H;
        int total = 0;
        for (int i = L; i <= H; i++)
        {
            if (number[i])
            {
                if (total++) cout << ' ';
                cout << i;
            }    
        }
        if (total == 0) cout << "-1";
        cout << '\n';
    }

    return 0;
}
