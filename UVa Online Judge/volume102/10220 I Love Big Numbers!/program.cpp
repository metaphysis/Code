// I Love Big Numbers!
// UVa ID: 10220
// Verdict: Accepted
// Submission Date: 2018-03-08
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

int getSum(int n)
{
    int sum = 0;
    while (n)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> digits;
    int sum[1010] = {1, 1};

    digits.push_back(1);
    for (int i = 2; i <= 1000; i++)
    {
        sum[i] = 0;
        int carry = 0;
        for (int j = 0; j < digits.size(); j++)
        {
            digits[j] = digits[j] * i + carry;
            carry = digits[j] / 10000;
            digits[j] %= 10000;
            sum[i] += getSum(digits[j]);
        }
        if (carry) digits.push_back(carry);
        sum[i] += getSum(carry);
    }

    int n;
    while (cin >> n) cout << sum[n] << '\n';

    return 0;
}
