// Egypt
// UVa ID: 11854
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

typedef long long ll;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    ll a, b, c;
    
    while (cin >> a >> b >> c, a > 0)
    {
        if (c < a) swap(a, c);
        if (c < b) swap(b, c);
        if ((a * a + b * b) == (c * c)) cout << "right\n";
        else cout << "wrong\n";
    }

    return 0;
}
