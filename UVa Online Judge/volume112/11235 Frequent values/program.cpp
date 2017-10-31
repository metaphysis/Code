// Frequent values  
// UVa ID: 11235
// Verdict: Accepted
// Submission Date: 2017-10-31
// UVa Run Time: 0.120s
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

const int MAXV = 100010;
int st[4 * MAXV], frequency[MAXV], boundary[MAXV][2];

void build(int p, int left, int right)
{
    if (left == right) st[p] = frequency[left];
    else {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        st[p] = max(st[(p << 1) + 1], st[(p + 1) << 1]);
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qleft > right || qright < left) return 0;
    if (qleft <= left && qright >= right) return st[p];
    int middle = (left + right) >> 1;
    return max(query((p << 1) + 1, left, middle, qleft, qright),
        query((p + 1) << 1, middle + 1, right, qleft, qright));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, q, a1, a2, ai, aj, cnt, start, end;
    while (cin >> n >> q)
    {
        cnt = 1, start = end = 0;
        
        cin >> a1;
        for (int i = 1; i < n; i++)
        {
            cin >> a2;
            if (a1 == a2) cnt++, end++;
            else
            {
                for (int j = start; j <= end; j++)
                {
                    frequency[j] = cnt;
                    boundary[j][0] = start, boundary[j][1] = end;
                }
                cnt = 1;
                start = end = i;
                a1 = a2;
            }
        }
        for (int j = start; j <= end; j++)
        {
            frequency[j] = cnt;
            boundary[j][0] = start, boundary[j][1] = end;
        }

        build(0, 0, n - 1);

        for (int i = 1; i <= q; i++)
        {
            cin >> ai >> aj;
            ai--, aj--;
            
            // becareful!
            if (boundary[ai][1] >= aj || boundary[aj][0] <= ai)
            {
                cout << (aj - ai + 1) << '\n';
                continue;
            }

            int left = 0, middle = 0, right = 0;
            
            if (ai > boundary[ai][0])
            {
                left = boundary[ai][1] - ai + 1;
                ai = boundary[ai][1] + 1;
            }
            
            if (aj < boundary[aj][1])
            {
                right = aj - boundary[aj][0] + 1;
                aj = boundary[aj][0] - 1;
            }

            // beware!
            if (ai <= aj) middle = query(0, 0, n - 1, ai, aj);

            cout << max(max(left, right), middle) << '\n';
        }
    }
    
    return 0;
}
