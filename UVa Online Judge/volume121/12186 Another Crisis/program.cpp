// Another Crisis
// UVa ID: 12186
// Verdict: Accepted
// Submission Date: 2018-02-20
// UVa Run Time: 0.090s
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

const int MAXV = 100010;

list<int> edges[MAXV];
int N, T, cnt[MAXV];

void dfs(int u)
{
    if (edges[u].size() == 0)
    {
        cnt[u] = 1;
        return;
    }

    vector<int> needed;
    for (auto v : edges[u])
    {
        dfs(v);
        needed.push_back(cnt[v]);
    }
    sort(needed.begin(), needed.end());
    int k = needed.size() * T / 100 + (needed.size() * T % 100 != 0);
    for (int i = 0; i < needed.size(); i++)
        if (i < k) cnt[u] += needed[i];
        else break;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> T, N > 0)
    {
        int u;
        for (int i = 0; i <= N; i++) edges[i].clear();
        for (int i = 1; i <= N; i++)
        {
            cin >> u;
            edges[u].push_back(i);
        }

        memset(cnt, 0, sizeof(cnt));
        dfs(0);
        cout << cnt[0] << '\n';
    }

    return 0;
}
