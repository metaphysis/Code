// The Bus Driver Problem
// UVa ID: 11389
// Verdict: Accepted
// Submission Date: 2017-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, d, r;
    int monring[110], evening[110];
    
    while (cin >> n >> d >> r, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> monring[i];
        for (int i = 0; i < n; i++) cin >> evening[i];

        sort(monring, monring + n, greater<int>());
        sort(evening, evening + n, less<int>());
        
        int exceeded = 0;
        for (int i = 0; i < n; i++)
            if (monring[i] + evening[i] > d)
                exceeded += (monring[i] + evening[i] - d);
        exceeded *= r;
        cout << exceeded << '\n';
    }

    return 0;
}
