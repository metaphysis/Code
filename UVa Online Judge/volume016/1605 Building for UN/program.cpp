// Building for UN
// UVa ID: 1605
// Verdict: Accepted
// Submission Date: 2021-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    //clock_t start = clock();
    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string countries;
    for (int i = 0; i < 26; i++)
    {
        countries += (char)(65 + i);
        countries += (char)(97 + i);
    }
    int cases = 0, n;
    while (cin >> n)
    {
        if (cases++) cout << '\n';
        cout << 2 << ' ' << n << ' ' << n << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << countries[j];
            cout << '\n';
        }
        cout << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << countries[i];
            cout << '\n';
        }
    }
    //clock_t finish = clock();
    //cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << " seconds.\n";

    return 0;
}
