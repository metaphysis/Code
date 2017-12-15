// The Lazy Lumberjacks
// UVa ID: 11936
// Verdict: Accepted
// Submission Date: 2017-12-15
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

    int cases, a, b, c;
    cin >> cases;
    
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> a >> b >> c;
        if ((a + b) <= c || (a + c) <= b || (b + c) <= a)
        {
            cout << "Wrong!!\n";
        }
        else
            cout << "OK\n";
    }

    return 0;
}
