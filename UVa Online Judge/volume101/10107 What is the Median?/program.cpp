// What is the Median?
// UVa ID: 10107
// Verdict: Accepted
// Submission Date: 2017-12-02
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int number[10010], n, k = 0;
    
    while (cin >> n)
    {
        number[k++] = n;
        for (int i = k - 1; i >= 1; i--)
        {
            if (n < number[i - 1])
                swap(number[i - 1], number[i]);
            else
                break;
        }

        if (k % 2 == 0) cout << (number[k / 2] + number[k / 2 - 1]) / 2 << '\n';
        else cout << number[k / 2] << '\n';
    }

    return 0;
}
