// Prerequisites?
// UVa ID: 10919
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int k, m;
    string cource;

    while (cin >> k, k > 0)
    {
        cin >> m;
        set<string> selected;
        for (int i = 1; i <= k; i++)
        {
            cin >> cource;
            selected.insert(cource);
        }
        bool fulfilled = true;
        for (int i = 1; i <= m; i++)
        {
            int c, r;
            cin >> c >> r;
            for (int j = 1; j <= c; j++)
            {
                cin >> cource;
                if (selected.find(cource) != selected.end()) r--;
            }
            if (r > 0) fulfilled = false;
        }
        if (fulfilled) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}
