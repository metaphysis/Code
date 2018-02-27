// Magic Formula
// UVa ID: 11934
// Verdict: Accepted
// Submission Date: 2018-02-27
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

    long long a, b, c, d, L;
    while (cin >> a >> b >> c >> d >> L, d > 0)
    {
        int cnt = 0;
        for (long long i = 0; i <= L; i++)
            if ((a * i * i + b * i + c) % d == 0)
                cnt++;
        cout << cnt << '\n';
    }
    return 0;
}
