// Place the Guards
// UVa ID: 10094
// Verdict: Accepted
// Submission Date: 2017-09-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int n, k;

    while (cin >> n)
    {
        if (n <= 3)
        {
            cout << "Impossible\n";
            continue;
        }

        if (n % 6 != 2 && n % 6 != 3)
        {
            cout << 2;
            for (int i = 4; i <= n; i += 2) cout << ' ' << i;
            for (int i = 1; i <= n; i += 2) cout << ' ' << i;
        }
        else
        {
            if (n & 1) k = (n - 1) / 2;
            else k = n / 2;

            if (k % 2 == 0 && n % 2 == 0)
            {
                cout << k;
                for (int i = k + 2; i <= n; i += 2) cout << ' ' << i;
                for (int i = 2; i <= k - 2; i += 2) cout << ' ' << i;
                for (int i = k + 3; i <= n - 1; i += 2) cout << ' ' << i;
                for (int i = 1; i <= k + 1; i += 2) cout << ' ' << i;
            }
            if (k % 2 == 0 && n % 2 == 1)
            {
                cout << k;
                for (int i = k + 2; i <= n - 1; i += 2) cout << ' ' << i;
                for (int i = 2; i <= k - 2; i += 2) cout << ' ' << i;
                for (int i = k + 3; i <= n - 2; i += 2) cout << ' ' << i;
                for (int i = 1; i <= k + 1; i += 2) cout << ' ' << i;
                cout << ' ' << n;
            }
            if (k % 2 == 1 && n % 2 == 0)
            {
                cout << k;
                for (int i = k + 2; i <= n - 1; i += 2) cout << ' ' << i;
                for (int i = 1; i <= k - 2; i += 2) cout << ' ' << i;
                for (int i = k + 3; i <= n; i += 2) cout << ' ' << i;
                for (int i = 2; i <= k + 1; i += 2) cout << ' ' << i;
            }
            if (k % 2 == 1 && n % 2 == 1)
            {
                cout << k;
                for (int i = k + 2; i <= n - 2; i += 2) cout << ' ' << i;
                for (int i = 1; i <= k - 2; i += 2) cout << ' ' << i;
                for (int i = k + 3; i <= n - 1; i += 2) cout << ' ' << i;
                for (int i = 2; i <= k + 1; i += 2) cout << ' ' << i;
                cout << ' ' << n;
            }
        }
        cout << '\n';
    }

    return 0;
}
