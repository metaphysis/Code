// String Popping
// UVa ID: 1261
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

bool isA(string s)
{
}

bool isB(string s)
{
    if (s.length() == 1 && s.front() == 'b') return true;
    if (s.length() > 0) return 
    return false;
}

bool isEmpty(string s)
{
    if (s.length() == 0) return true;
    if (s.back() == 'b') return isB(s.substr(0, s.length() - 1))
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        cout << (isEmpty(line) ? 1 : 0) << '\n';
    }

    return 0;
}
