// The dominoes solitaire
// UVa ID: 10503
// Verdict: Accepted
// Submission Date: 2017-11-12
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

int n, m, dominoes[15][2], used[20];
int dot1, dot2, head, tail;
int finished = 0;

void dfs(int depth, int ending)
{
    if (depth == n)
    {
        if (ending == tail) finished = 1;
        return;
    }
    
    for (int i = 0; i < m; i++)
    {
        if (used[i]) continue;
        if (dominoes[i][0] == ending)
        {
            used[i] = 1;
            dfs(depth + 1, dominoes[i][1]);
            used[i] = 0;
        }
        if (dominoes[i][0] != dominoes[i][1] && dominoes[i][1] == ending)
        {
            used[i] = 1;
            dfs(depth + 1, dominoes[i][0]);
            used[i] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        cin >> m;
        
        cin >> dot1 >> dot2;
        head = dot2;
        cin >> dot1 >> dot2;
        tail = dot1;
        
        for (int i = 0; i < m; i++)
            cin >> dominoes[i][0] >> dominoes[i][1];

        memset(used, 0, sizeof(used));
        finished = 0;
        dfs(0, head);
        
        cout << (finished ? "YES" : "NO") << '\n';
    }

    return 0;
}
