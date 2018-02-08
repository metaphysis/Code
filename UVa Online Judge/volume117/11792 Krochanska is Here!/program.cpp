// Krochanska is Here!
// UVa ID: 11792
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.150s
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

list<int> edges[10010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, S, cnt[10010], visited[10010], dist[10010];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> S;
        for (int i = 1; i <= N; i++)
            edges[i].clear();
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < S; i++)
        {
            int s1, s2;
            cin >> s1;
            if (s1 > 0)
            {
                cnt[s1]++;
                while (cin >> s2, s2 > 0)
                {
                    edges[s1].push_back(s2);
                    edges[s2].push_back(s1);
                    s1 = s2;
                    cnt[s2]++;
                }
            }
        }

        vector<int> important;
        for (int i = 1; i <= N; i++)
            if (cnt[i] >= 2)
                important.push_back(i);

        int minHours = 0x7fffffff, X = -1;
        for (auto impt1 : important)
        {
            memset(visited, 0, (N + 1) * sizeof(int));
            queue<int> q;
            q.push(impt1);
            visited[impt1] = 1;
            dist[impt1] = 0;
            
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (auto v : edges[u])
                    if (!visited[v])
                    {
                        visited[v] = 1;
                        q.push(v);
                        dist[v] = dist[u] + 1;
                    }
            }

            int currentHours = 0;
            for (auto impt2 : important)
                currentHours += dist[impt2]; 
            if (minHours > currentHours)
            {
                minHours = currentHours;
                X = impt1;
            }
        }
        cout << "Krochanska is in: " << X << '\n';
    }

    return 0;
}
