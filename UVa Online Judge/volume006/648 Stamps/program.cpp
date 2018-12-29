// Stamps
// UVa ID: 648
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> best;
int types, total, highest;
int stamps[32], n, request, used[4];

void dfs(int depth, int idx, int value)
{
    if (depth > 4 || value > request) return;
    if (d == request)
    {
        bool better = false;
        set<int> diff;
        for (int i = 0; i < depth; i++)
            diff.insert(used[i]);
        if (diff.size() > types)
        {
            best.clear();
            better = true;
        }
        else if (diff.size() == types)
        {
            if (depth + 1 < total)
            {
                best.clear();
                better = true;
            }
            else if (depth + 1 == total)
            {
                int h = 0;
                for (int i = 0; i < depth; i++)
                    h = max(h, stamps[used[i]]);
                if (h > highest)
                {
                    best.clear();
                    better = true;
                }
                else if (h == highest)
                {
                    better = true;
                }
            }
        }
        
        if (better)
        {
            types = diff.size();
            total = depth + 1;
            highest = 0;
            for (int i = 0; i < depth; i++)
                highest = max(highest, stamps[used[i]]);
            vector<int> vs;
            for (int s = 0; s < depth; s++)
                vs.push_back(stamps[used[s]]);
            sort(vs.begin(), vs.end());
            best.push_back(vs);
        }
        return;
    }
    for (int i = idx; i < n; i++)
    {
        used[depth] = i;
        dfs(depth + 1, i, value + stamps[i]);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int value;
    while (cin >> value)
    {
        n = 0;
        stamps[n++] = value;
        while (cin >> value, value > 0)
            stamps[n++] = value;

        while (cin >> request, request > 0)
        {
            best.clear();
            types = 0, total = 10, highest = 0;
            dfs(0, 0, 0);
            cout << request;
            if (best.size() == 0) cout << " ---- none\n";
            else
            {
                cout << " (" << types << "):";
                if (best.size() == 1)
                {
                    for (int i = 0; i < best[0].size(); i++)
                        cout << ' ' << best[0][i];
                    cout << '\n';
                }
                else cout << " tie\n";
            }
        }
    }

    return 0;
}
