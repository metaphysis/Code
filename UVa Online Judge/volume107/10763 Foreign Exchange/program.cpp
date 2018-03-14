// Foreign Exchange
// UVa ID: 10763
// Verdict: Accepted
// Submission Date: 2017-10-14
// UVa Run Time: 0.090s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct exchange
{
    int x, y;
    
    bool operator<(const exchange &e) const
    {
        if (x != e.x) return x < e.x;
        else return y < e.y;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, x, y;
    while (cin >> n, n > 0)
    {
        vector<exchange> a, b;
        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y;
            if (x < y) a.push_back(exchange{x, y});
            else b.push_back(exchange{y, x});
        }
        
        if ((n % 2) == 1) cout << "NO\n";
        else
        {
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            
            if (a.size() != b.size()) cout << "NO\n";
            else
            {
                bool same = true;
                for (int i = 0; i < a.size(); i++)
                    if (a[i].x != b[i].x || a[i].y != b[i].y)
                    {
                        same = false;
                        break;
                    }
                    
                cout << (same ? "YES" : "NO") << '\n';
            }
        }
    }
    
    return 0;
}
