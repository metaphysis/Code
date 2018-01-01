// No Problem!
// UVa ID: 11608
// Verdict: Accepted
// Submission Date: 2018-01-01
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

    int s, cases = 0, created[12], needed[12];
    while (cin >> s, s >= 0)
    {
        for (int i = 0; i < 12; i++) cin >> created[i];
        for (int i = 0; i < 12; i++) cin >> needed[i];
        cout << "Case " << ++cases << ":\n";
        for (int i = 0; i < 12; i++)
        {
            if (s >= needed[i]) { cout << "No problem! :D\n"; s -= needed[i]; }
            else cout << "No problem. :(\n";
            s += created[i];
        }
    }
    return 0;
}
