// Let’s Play Magic!
// UVa ID: 10978
// Verdict: Accepted
// Submission Date: 2017-12-31
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

    int n, used[52];
    string cards[52], value, suit;

    while (cin >> n, n > 0)
    {
        memset(used, 0, sizeof(used));
        int idx = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> value >> suit;
            int cnt = 0;
            while (true)
            {
                if (!used[idx]) cnt++;
                if (cnt == suit.length()) break;
                idx = (idx + 1) % n;
            }
            cards[idx] = value;
            used[idx] = 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (i) cout << ' ';
            cout << cards[i];
        }
        cout << '\n';
    }

    return 0;
}
