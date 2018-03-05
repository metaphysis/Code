// Nice Licence Plates
// UVa ID: 12602
// Verdict: Accepted
// Submission Date: 2018-03-05
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
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        string text = line.substr(0, 3);
        int n1 = (text[0] - 'A') * 26 * 26 + (text[1] - 'A') * 26 + text[2] - 'A';
        int n2 = stoi(line.substr(4, 4));
        if (abs(n1 - n2) <= 100) cout << "nice\n";
        else cout << "not nice\n";
    }

    return 0;
}
