// Power of Cryptography
// UVa ID: 113
// Verdict: Accepted
// Submission Date: 2017-12-18
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

    long double n, p;
    
    while (cin >> n >> p)
    {
        cout << fixed << setprecision(0) << pow(p, 1 / n) << '\n';
    }

    return 0;
}
