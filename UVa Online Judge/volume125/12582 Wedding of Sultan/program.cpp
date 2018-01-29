// Wedding of Sultan
// UVa ID: 12582
// Verdict: Accepted
// Submission Date: 2018-01-29
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

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        string line;
        cin >> line;
        map<char, int> trails;
        stack<char> visited;
        for (auto letter : line)
        {
            if (visited.empty()) visited.push(letter);
            else
            {
                trails[visited.top()]++;
                if (letter == visited.top()) visited.pop();
                else visited.push(letter);
            }
        }
        trails[line.front()]--;
        cout << "Case " << c << '\n';
        for (auto t : trails)
        {
            cout << t.first << " = " << t.second << '\n';
        }
    }

    return 0;
}
