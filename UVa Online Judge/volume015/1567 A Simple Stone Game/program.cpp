// A Simple Stone Game
// UVa ID: 1567
// Verdict: Accepted
// Submission Date: 2019-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000000;
int a[MAXN] = {}, b[MAXN] = {};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> k;
        a[0] = b[0] = 1;
        int i = 0, j = 0;
        while (a[i] < n)
        {
            i++;
            a[i] = b[i - 1] + 1;
            while (a[j + 1] * k < a[i]) j++;
            if (a[j] * k < a[i]) b[i] = b[j] + a[i];
            else b[i] = a[i];
        }
        cout << "Case " << cs << ": ";
        if (a[i] == n) cout << "lose\n";
        else
        {
            int moved;
            while (n)
            {
                if (n >= a[i]) n -= a[i], moved = a[i];
                i--;
            }
            cout << moved << '\n';
        }
    }

    return 0;
}
