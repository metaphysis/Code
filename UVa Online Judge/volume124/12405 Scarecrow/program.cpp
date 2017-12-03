// Scarecrow
// UVa ID: 12405
// Verdict: Accepted
// Submission Date: 2017-12-03
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

    int cases, n;
    char cell;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        string block;
        int scarecrow = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> cell;
            block += cell;
            if (block.front() == '#') block.erase(block.begin());
            if (block.length() == 3)
            {
                scarecrow++;
                block.clear();
            }
        }
        if (block.length() > 0) scarecrow++;
        cout << "Case " << c << ": " << scarecrow << '\n';
    }

    return 0;
}
