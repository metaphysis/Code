// Fractions Again?!
// UVa ID: 10976
// Verdict: Accepted
// Submission Date: 2017-07-25
// UVa Run Time: 0.010s
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

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int k;
    
    while (cin >> k)
    {
        vector<pair<int, int>> pairs;
        
        int up = 2 * k, numerator, denominator;
        for (int i = k + 1; i <= up; i++)
        {
            numerator = i - k, denominator = i * k;
            int g = gcd(numerator, denominator);
            numerator /= g, denominator /= g;
            if (numerator == 1 && denominator >= i)
                pairs.push_back(make_pair(denominator, i));
        }

        cout << pairs.size() << '\n';
        for (auto pair : pairs)
            cout << "1/" << k << " = 1/" << pair.first << " + 1/" << pair.second << '\n';
    }
    
    return 0;
}
