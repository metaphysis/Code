// Good Teacher
// UVa ID: 12662
// Verdict: Accepted
// Submission Date: 2021-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string name[128];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> name[i];
    int q, p;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> p;
        p--;
        if (name[p] != "?") cout << name[p] << '\n';
        else
        {
            int l = p, r = p;
            while (l >= 0 && name[l] == "?") l--;
            while (r < n && name[r] == "?") r++;
            if (l == -1)
            {
                for (int j = 0; j < r - p; j++) cout << "left of ";
                cout << name[r] << '\n';
            }
            else if (r == n)
            {
                for (int j = 0; j < p - l; j++) cout << "right of ";
                cout << name[l] << '\n';
            }
            else
            {
                int dl = p - l, dr = r - p;
                if (dl == dr)
                {
                    cout << "middle of " << name[l] << " and " << name[r] << '\n';
                }
                else if (dl < dr)
                {
                    for (int j = 0; j < p - l; j++) cout << "right of ";
                    cout << name[l] << '\n';
                }
                else
                {
                    for (int j = 0; j < r - p; j++) cout << "left of ";
                    cout << name[r] << '\n';
                }
            }
        }
    }

    return 0;
}
