// Bachet's Game
// UVa ID: 10404
// Verdict: Accepted
// Submission Date: 2018-02-06
// UVa Run Time: 0.300s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int sg[1000010], n, m, a[20];

int grundy(int x)
{
    if (sg[x] < 0)
    {
        set<int> s;
        for (int i = 0; i < m; i++)
            if (a[i] <= x)
                s.insert(grundy(x - a[i]));
        int g = 0;
        while (s.find(g) != s.end()) g++;
        sg[x] = g;
    }
    return sg[x];
}

void solve()
{
    while (cin >> n)
    {
        cin >> m;
        for (int i = 0; i < m; i++)
            cin >> a[i];
        sg[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            set<int> s;
            for (int j = 0; j < m; j++)
                if (a[j] <= i)
                    s.insert(sg[i - a[j]]);
            int g = 0;
            while (s.find(g) != s.end()) g++;
            sg[i] = g;
        }
        if (sg[n]) cout << "Stan wins\n";
        else cout << "Ollie wins\n";
    }
}

const int MAXN = 1000010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int n, m, a[16];
    bool win[MAXN];

    while (cin >> n)
    {
        cin >> m;
        for (int i = 0; i < m; i++) cin >> a[i];

        win[0] = false;
        for (int i = 1; i <= n; i++)
        {
            win[i] = false;
            for (int j = 0; j < m; j++)
            win[i] |= ((a[j] <= i) && !win[i - a[j]]);
        }

        if (win[n]) cout << "Stan wins\n";
        else cout << "Ollie wins\n";
    }
    
    return 0;
}
