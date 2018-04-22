// Magic Square
// UVa ID: 1266
// Verdict: Accepted
// Submission Date: 2018-04-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 24;

void fillMagic(int n, int magic[][MAXN])
{
    int i = 0, j = n / 2;
    for (int k = 1; k <= n * n; k++)
    {
        magic[i][j] = k;
        if (k % n)
        {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        else
            i = (i + 1) % n;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int n, cases = 0;
    while (cin >> n)
    {
        if (cases++ > 0) cout << '\n';
        cout << "n=" << n << ", sum=" << n * (n * n + 1) / 2 << '\n';
        int magic[24][24] = {0}, maxWidth[24] = {0};
        fillMagic(n, magic);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                maxWidth[j] = max(maxWidth[j], (int)to_string(magic[i][j]).length());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << setw(maxWidth[j] + 1) << right << magic[i][j];
            cout << '\n';
        }
    }

    return 0;
}
