// No More Prerequisites, Please!
// UVa ID: 925
// Verdict: Accepted
// Submission Date: 2018-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 128;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, linked[MAXV][MAXV], n, m;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        map<string, int> indexer;
        map<int, string> names;
        vector<int> pre[MAXV];
        set<string> result;
        string name1, name2;

        memset(linked, false, sizeof(linked));

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> name1;
            indexer[name1] = i;
            names[i] = name1;
            pre[i].clear();
            linked[i][i] = true;
        }
        cin >> m;
        for (int i = 1, j, v; i <= m; i++)
        {
            cin >> name1 >> j;
            v = indexer[name1];
            result.insert(name1);
            for (int k = 1, u; k <= j; k++)
            {
                cin >> name2;
                u = indexer[name2];
                linked[u][v] = true;
                pre[v].push_back(u);
            }
        }
        
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    linked[i][j] |= linked[i][k] && linked[k][j];
                    
        for (auto r : result)
        {
            set<string> minimum;
            int idx = indexer[r];
            for (auto u : pre[idx])
            {
                bool contained = false;
                for (auto v : pre[idx])
                {
                    if (u == v) continue;
                    if (linked[u][v])
                    {
                        contained = true;
                        break;
                    }
                }
                if (!contained) minimum.insert(names[u]);
            }
            cout << r << ' ' << minimum.size();
            for (auto course : minimum) cout << ' ' << course;
            cout << '\n';
        }
    }

    return 0;
}
