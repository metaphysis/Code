// Biorhythms
// UVa ID: 756
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, e, i, d, cases = 0;
    while (cin >> p >> e >> i >> d)
    {
        if (p == -1) break;

        p %= 23, e %= 28, i %= 33;
        int s = max(max(p, e), max(i, d));
        if (d == s) s++;
        while (true)
        {
            if ((s - p) % 23 == 0 && (s - e) % 28 == 0 && (s - i) % 33 == 0)
                break;
            s++;
        }
        
        cout << "Case " << ++cases << ": the next triple peak occurs in ";
        cout << (s - d) << " days.\n";
    }

    return 0;
}
