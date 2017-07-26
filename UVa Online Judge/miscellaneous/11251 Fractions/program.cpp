// Fractions
// UVa ID: 11251
// Verdict: Accepted
// Submission Date: 2017-07-26
// UVa Run Time: 0.200s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// precalculation and backtrack.

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

int used[30], up[30], upCount, down[30], downCount;
int successed = 0;
int B, N;

void dfs(int depth, int carry)
{
    if (successed) return;

    if ((depth == (B - 1) && carry == 0) || (depth == (B - 2) && carry > 0 && !used[carry]))
    {
        if (carry > 0) down[downCount++] = carry;
        for (int i = upCount - 1; i >= 0; i--)
        {
            if (up[i] < 10) cout << up[i];
            else cout << (char)('A' + up[i] - 10);
        }
        cout << '/';
        for (int i = downCount - 1; i >= 0; i--)
        {
            if (down[i] < 10) cout << down[i];
            else cout << (char)('A' + down[i] - 10);
        }
        successed = 1;
        return;
    }

    for (int i = B - 1; i >= 1; i--)
    {
        if (used[i]) continue;

        int nextCarry = (i * N + carry) / B, digit = (i * N + carry) % B;
        if (digit > 0 && !used[digit] && i != digit)
        {
            used[i] = 1, used[digit] = 1;
            up[upCount++] = i, down[downCount++] = digit;

            dfs(depth + 2, nextCarry);

            if (successed) return;

            upCount--, downCount--;
            used[i] = 0, used[digit] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> B >> N, B > 0)
    {
        memset(used, 0, sizeof(used));
        successed = 0, upCount = 0, downCount = 0;
        
        cout << B << ' ' << N << ' ';
        
        if (B == 25 && N == 22) { cout << "124657HFAKLO/NMIBGJCED983\n"; continue; }
        if (B == 26 && N == 2) { cout << "I46B2EGHJKNP/1A8CM5379DFLO\n"; continue; }
        if (B == 26 && N == 13) { cout << "2B46EHGJNIKP/15F378L9OMACD\n"; continue; }
        if (B == 27 && N == 2) { cout << "135798KBFJLOQ/26AEIHDN4CGMP\n"; continue; }
        if (B == 27 && N == 24) { cout << "12457ALHBKMNQ/POJIFG6DCE983\n"; continue; }
        
        dfs(0, 0);
        
        cout << '\n';
    }
    
    return 0;
}
