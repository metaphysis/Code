// Excessive Space Remover
// UVa ID: 12416
// Verdict: Accepted
// Submission Date: 2018-03-07
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
    cin.unsetf(ios::skipws);
    
    char letter;
    while (cin >> letter)
    {
        int spaces = 0, n = 0;
        if (letter == ' ') n++;
        while (cin >> letter)
        {
            if (letter == ' ') n++;
            else
            {
                spaces = max(spaces, n);
                n = 0;
            }
            if (letter == '\n') break;
        }
        int x = 0;
        while (spaces > 1) x++, spaces = (spaces + 1) / 2;
        cout << x << '\n';
    }

    return 0;
}
