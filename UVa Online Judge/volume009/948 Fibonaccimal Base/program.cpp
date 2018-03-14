// Fibonaccimal Base
// UVa ID: 948
// Verdict: Accepted
// Submission Date: 2017-02-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 40;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int fibs[MAXN] = { 1, 2 };
    for (int i = 2; i < MAXN; i++)
        fibs[i] = fibs[i - 1] + fibs[i - 2];

    int n, m;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> m;
        cout << m << " = ";

        int j = 39;
        bool started = false;
        while (m)
        {
            if (m >= fibs[j])
            {
                started = true;
                cout << '1';
                if (j > 0)
                    cout << '0';
                m -= fibs[j];
                j -= 2;
            }
            else
            {
                if (started)
                    cout << '0';
                j -= 1;
            }
        }

        while (j >= 0)
        {
            cout << '0';
            j -= 1;
        }

        cout << " (fib)\n";
    }

    return 0;
}
