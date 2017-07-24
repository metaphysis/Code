// Dead Fraction
// UVa ID: 10555
// Verdict: Accepted
// Submission Date: 2017-07-24
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

long long gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

pair<long long, long long> getFraction(string fraction, int j)
{
    long long numerator, denominator;

    size_t dot = fraction.find('.');
    if (dot != fraction.npos) fraction = fraction.substr(dot + 1);
    
    if (j == 0)
    {
        numerator = stoll(fraction);
        denominator = pow(10, fraction.length());
    }
    else
    {
        int k = fraction.length() - j;
        string preRepeated = fraction.substr(0, k);
        if (preRepeated.length() == 0) preRepeated = "0";
        
        numerator = stoll(fraction) - stoll(preRepeated);
        denominator = pow(10, k + j) - pow(10, k);
    }
    
    long long g = gcd(numerator, denominator);

    return make_pair(numerator / g, denominator / g);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string fraction;
    while (cin >> fraction, fraction != "0")
    {
        fraction = fraction.substr(0, fraction.length() - 3);

        pair<long long, long long> best;
        int up = fraction.length() - 2, bestSetted = 0;

        for (int j = 1; j <= up; j++)
        {
            pair<long long, long long> r = getFraction(fraction, j);
            if (!bestSetted || r.second < best.second) best = r, bestSetted = 1;
        }

        cout << best.first << '/' << best.second << '\n';
    }
    
    return 0;
}
