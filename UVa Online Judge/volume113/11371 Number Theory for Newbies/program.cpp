// Number Theory for Newbies
// UVa ID: 11371
// Verdict: Accepted
// Submission Date: 2018-03-12
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

    int n, digit[12];
    while (cin >> n)
    {
        vector<int> digits;
        int x = n;
        while (x)
        {
            digits.push_back(x % 10);
            x /= 10;
        }
        sort(digits.begin(), digits.end(), greater<int>());
        long long a = 0;
        for (auto d : digits)
            a = a * 10 + d;
        sort(digits.begin(), digits.end());
        if (digits.front() == 0)
        {
            for (int i = 0; i < digits.size(); i++)
                if (digits[i])
                {
                    swap(digits[0], digits[i]);
                    break;
                }
        }
        long long b = 0;
        for (auto d : digits)
            b = b * 10 + d;
        cout << a << " - " << b << " = " << (a - b) << " = 9 * " << (a - b) / 9 << '\n';
    }

    return 0;
}
