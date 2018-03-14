// Water Gate Management
// UVa ID: 12346
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct gate
{
    int volume, cost;
    bool operator<(const gate &g) const
    {
        if (cost != g.cost) return cost < g.cost;
        return volume > g.volume;
    }
    
    bool operator==(const gate &g) const
    {
        return volume == g.volume && cost == g.cost;
    }
} gates[24];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, v, t, vt = 0;
    
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> gates[i].volume >> gates[i].cost;
        vt += gates[i].volume;
    }
        
    vector<gate> all;
    for (int i = 0; i < n; i++)
    {
        int current = all.size();
        all.push_back(gates[i]);
        for (int j = 0; j < current; j++)
        {
            gate next = gate{all[j].volume + gates[i].volume, all[j].cost + gates[i].cost};
            all.push_back(next);
        }
    }
    
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cout << "Case " << i << ": ";
        
        cin >> v >> t;
        bool flag = false;

        if (vt * t >= v)
        {
            for (int j = 0; j < all.size(); j++)
                if (all[j].volume * t >= v)
                {
                    cout << all[j].cost << '\n';
                    flag = true;
                    break;
                }
        }

        if (!flag) cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
