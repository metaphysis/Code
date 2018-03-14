// Lumberjack Sequencing
// UVa ID: 11942
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

    cout << "Lumberjacks:\n";

    int cases, h1, h2;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int up = 0, down = 0;

        cin >> h1;
        for (int i = 1; i <= 9; i++)
        {
            cin >> h2;
            if (h1 >= h2) down++;
            if (h1 <= h2) up++;
            h1 = h2;
        }
            
        if (down == 9 || up == 9) cout << "Ordered";
        else cout << "Unordered";

        cout << '\n'; 
    }

    return 0;
}
