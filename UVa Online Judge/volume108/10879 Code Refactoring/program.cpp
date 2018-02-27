// Code Refactoring
// UVa ID: 10879
// Verdict: Accepted
// Submission Date: 2018-02-26
// UVa Run Time: 0.010s
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

    int cases, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ": ";
        cin >> n;
        cout << n;
        for (int i = 2, j = 0; j < 2; i++)
            if (n % i == 0)
            {
                cout << " = " << i << " * " << (n / i);
                j++;
            }
        cout << '\n';
    }

    return 0;
}
