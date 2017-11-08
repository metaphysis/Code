// Rat Attack
// UVa ID: 10360
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.050s
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

const int MAXV = 1024;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int rats[MAXV + 1][MAXV + 1], d, n;
    int x, y, s;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> d >> n;

        memset(rats, 0, sizeof(rats));

        for (int i = 0; i < n; i++)
        {
            cin >> x >> y >> s;

            int lowj = x - d, upj = x + d;
            if (lowj < 0) lowj = 0;
            if (upj > MAXV) upj = MAXV;
            
            int lowk = y - d, upk = y + d;
            if (lowk < 0) lowk = 0;
            if (upk > MAXV) upk = MAXV;

            for (int j = lowj; j <= upj; j++)
                for (int k = lowk; k <= upk ; k++)
                    rats[j][k] += s;
        }

        int most = 0, selectedi, selectedj;
        for (int i = 0; i <= MAXV; i++)
            for (int j = 0; j <= MAXV; j++)
                if (rats[i][j] > most)
                {
                    most = rats[i][j];
                    selectedi = i, selectedj = j;
                }
        cout << selectedi << ' ' << selectedj << ' ' << most << '\n';
    }
    
    return 0;
}
