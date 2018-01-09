// Spiral Tap
// UVa ID: 10920
// Verdict: Accepted
// Submission Date: 2018-01-09
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

    long long SZ, P;
    
    while (cin >> SZ >> P)
    {
        if (SZ == 0 && P == 0) break;
        
        long long root = sqrt(P);
        if ((root & 1) == 0) root += 1;
        if (P > root * root) root += 2;

        //cout << "root = " << root << '\n';

        long long rightTop = root * root;
        long long rightBottom = rightTop - (root - 1);
        long long leftBottom = rightBottom - (root - 1);
        long long leftTop = leftBottom - (root - 1);
        
        //cout << "rightTop = " << rightTop << " rightBottom = " << rightBottom << " leftBottom = " << leftBottom << " leftTop = " << leftTop << '\n';

        long long rightX = SZ / 2 + 1 + root / 2, rightY = rightX;
        long long leftX = rightX - root + 1, leftY = leftX;
        
        //cout << "leftX = " << leftX << " leftY = " << leftY << " rightX = " << rightX << " rightY = " << rightY << '\n';

        int x, y;
        if (P >= rightBottom && P <= rightTop) x = rightX, y = rightY - (rightTop - P);
        else if (P >= leftBottom && P <= rightBottom) x = rightX - (rightBottom - P), y = leftY;
        else if (P >= leftTop && P <= leftBottom) x = leftX, y = leftY + (leftBottom - P);
        else x = leftX + (leftTop - P), y = rightY;
        
        cout << "Line = " << y << ", column = " << x << ".\n";
    }

    return 0;
}
