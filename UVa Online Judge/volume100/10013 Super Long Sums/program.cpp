// Super Long Sums
// UVa ID: 10013
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.370s
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

    int cases, number1[1000010], number2[1000010], m;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m;
        for (int i = 0; i < m; i++)
            cin >> number1[i] >> number2[i];
        int carry = 0;
        for (int i = m - 1; i >= 0; i--)
        {
            number1[i] += number2[i] + carry;
            carry = number1[i] / 10;
            number1[i] %= 10;
        }
        if (c > 1) cout << '\n';
        if (carry)
        {
            cout << 1;
            for (int i = 0; i < m; i++)
                cout << number1[i];
            cout << '\n';
        }
        else
        {
            for (int i = 0; i < m; i++)
            {
                if (!number1[i]) continue;
                for (int j = i; j < m; j++)
                    cout << number1[j];
                cout << '\n';
                break;
            }
        }
    }

    return 0;
}
