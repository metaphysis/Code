// Prime Substring
// UVa ID: 12542
// Verdict: Accepted
// Submission Date: 2018-03-02
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

const int MAXV = 100010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXV] = {0}, cnt = 0;
    for (int i = 2; i < MAXV; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXV; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }

    string line;
    while (getline(cin, line), line != "0")
    {
        int largest = 2;
        for (int i = 0; i < line.length(); i++)
        {
            int r = 0;
            for (int j = i; j < line.length(); j++)
            {
                r = r * 10 + line[j] - '0';
                if (r > primes[cnt - 1]) break;
                if (r != 2 && (r & 1) == 0) continue;
                if (binary_search(primes, primes + cnt, r))
                    largest = max(largest, r);
            }
        }
        cout << largest << '\n';
    }

    return 0;
}
