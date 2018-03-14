// Zapping
// UVa ID: 12468
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

    int a, b;
    
    while (cin >> a >> b)
    {
        if (a == -1) break;
        
        int up = (b >= a ? b - a : (99 - a + b + 1));
        int down = (b <= a ? a - b : (99 - b + a + 1));
        
        cout << min(up, down) << '\n';
    }

    return 0;
}
