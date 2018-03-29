// String Partition
// UVa ID: 11258
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_INT = numeric_limits<signed int>::max();

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string digits;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> digits;
        digits.insert(digits.begin(), '0');
        long long dp[256] = {};
        for (int i = 1; i < digits.length(); i++)
        {
            long long number = 0, weight = 1;
            for (int j = i; j >= 1; j--, weight *= 10)
            {
                if (j != i && digits[j] == '0') continue;
                number += (digits[j] - '0') * weight;
                if (number > MAX_INT) break;
                dp[i] = max(dp[i], dp[j - 1] + number);
            }
        }
        cout << *(max_element(dp, dp + 256)) << '\n';
    }

    return 0;
}
