// Tariff Plan
// UVa ID: 12157
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int Mile[2100], Juice[2100];
    
    for (int i = 0, fee = 10; i <= 2000; i += 30, fee += 10)
        for (int j = 0; j <= 29; j++)
            Mile[i + j] = fee;

    for (int i = 0, fee = 15; i <= 2000; i += 60, fee += 15)
        for (int j = 0; j <= 59; j++)
            Juice[i + j] = fee;
    
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n, call;
        int cm = 0, cj = 0;
        cin >> n;
        
        for (int i = 0; i < n; i++)
        {
            cin >> call;
            cm += Mile[call], cj += Juice[call];
        }
        
        cout << "Case " << cs << ": ";
        if (cm < cj) cout << "Mile " << cm << '\n';
        else if (cj < cm) cout << "Juice " << cj << '\n';
        else cout << "Mile Juice " << cm << '\n';
    }

    return 0;
}
