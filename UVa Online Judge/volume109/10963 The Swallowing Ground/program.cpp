// The Swallowing Ground
// UVa ID: 10963
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

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int n, y1, y2;
        
        cin >> n;

        cin >> y1 >> y2;
        int gap = abs(y1 - y2);
        
        int flag = 1;
        for (int i = 1; i < n; i++)
        {
            cin >> y1 >> y2;
            if (gap != abs(y1 - y2)) flag = 0;
        }
        
        if (c > 1) cout << '\n';
        cout << (flag ? "yes" : "no") << '\n';
    }

    return 0;
}
