// Problem with a ridiculously long name but with a ridiculously short description
// UVa ID: 13216
// Verdict: Accepted
// Submission Date: 2017-11-18
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

    string n;
    int cases, tail[5] = {76, 16, 56, 96, 36};
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        if (n == "0") { cout << "1\n"; continue; }
        if (n == "1") { cout << "66\n"; continue; }
        cout << tail[(n.back() - '0') % 5] << '\n';
    }

    return 0;
}
