// The Land of Justice
// UVa ID: 10499
// Verdict: Acccepted
// Submission Date: 2018-03-01
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

    long long N;
    while (cin >> N, N > 0)
    {
        if (N == 1) cout << "0%\n";
        else cout << (N * 25) << "%\n";
    }

    return 0;
}
