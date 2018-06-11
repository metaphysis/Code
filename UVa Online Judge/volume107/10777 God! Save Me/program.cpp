// God! Save Me
// UVa ID: 10777
// Verdict: Accepted
// Submission Date: 2018-06-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    double xi, pi, ex, pp;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        ex = pp = 0.0;
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> pi;
            ex += fabs(xi) * pi;
            if (xi > 0) pp += pi;
        }
        cout << "Case " << cs << ": ";
        if (pp == 0.0) cout << "God! Save me\n";
        else cout << fixed << setprecision(2) << ex / pp << '\n';
    }

    return 0;
}
