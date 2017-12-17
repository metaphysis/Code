// Combination Lock
// UVa ID: 10550
// Verdict: Accepted
// Submission Date: 2017-12-17
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

    int a, b, c, d;
    
    while (cin >> a >> b >> c >> d)
    {
        if (a == 0 && b == 0 && c == 0 && d == 0) break;
        int degrees = 360 * 3;

        int turn = a - b;
        if (turn < 0) turn += 40;
        degrees += turn * 9;

        turn = c - b;
        if (turn < 0) turn += 40;
        degrees += turn * 9;
        
        turn = c - d;
        if (turn < 0) turn += 40;
        degrees += turn * 9;

        cout << degrees << '\n';
    }

    return 0;
}
