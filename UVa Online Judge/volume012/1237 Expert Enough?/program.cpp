// Expert Enough?
// UVa ID: 1237
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct maker
{
    string name;
    int low, high;
    
    bool operator<(const maker &m) const
    {
        if (low != m.low) return low < m.low;
        return high < m.high;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, q, price;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> n;
        vector<maker> makers(n);
        for (int i = 0; i < n; i++)
            cin >> makers[i].name >> makers[i].low >> makers[i].high;
            
        sort(makers.begin(), makers.end());
        
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> price;

            maker doll1 = maker{"doll", 0, price - 1};
            maker doll2 = maker{"doll", price + 1, 0};

            auto start = lower_bound(makers.begin(), makers.end(), doll1);
            auto end = lower_bound(makers.begin(), makers.end(), doll2);

            int cnt = 0;
            string name;
            for (auto it = start; it != end; it++)
            {
                if ((*it).low <= price && (*it).high >= price)
                {
                    name = (*it).name;
                    cnt++;
                }
                if (cnt > 1) break;
            }

            if (cnt == 1) cout << name << '\n';
            else cout << "UNDETERMINED\n";
        }
    }

    return 0;
}
