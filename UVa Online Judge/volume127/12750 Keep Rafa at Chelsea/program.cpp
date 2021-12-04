// Keep Rafa at Chelsea
// UVa ID: 12750
// Verdict: Accepted
// Submission Date: 2021-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        char result;
        int n, lasted = 0, notwin = 0, sacked = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> result;
            if (!sacked)
            {
                lasted++;
                if (result == 'W') notwin = 0;
                else notwin++;
                if (notwin == 3) sacked = 1;
            }
        }
        if (!sacked) cout << "Yay! Mighty Rafa persists!";
        else cout << lasted;
        cout << '\n';
    }

    return 0;
}
