// Hours and Minutes
// UVa ID: 12531
// Verdict: Accepted
// Submission Date: 2017-12-29
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

    int degree[200] = {0};
    
    for (int hour = 0; hour <= 360; )
    {
        for (int minute = 0; minute <= 360; minute += 6)
        {
            if (minute && minute % 72 == 0)
            {
                hour += 6;
                int angle = min(abs(hour - minute), 360 - abs(hour - minute));
                degree[angle] = 1;
            }
        }
    }

    int A;
    while (cin >> A) cout << (degree[A] ? 'Y' : 'N') << '\n';

    return 0;
}
