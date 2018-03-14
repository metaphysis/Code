// Move the Bishop
// UVa ID: 10849
// Verdict: Accepted
// Submission Date: 2017-12-22
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
    for (int cs = 1; cs <= cases; cs++)
    {
        int ts, n;

        cin >> ts >> n;
        for (int ks = 1; ks <= ts; ks++)
        {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            
            if (r1 == r2 && c1 == c2)
            {
                cout << 0 << '\n';
                continue;
            }
            
            // 根据奇偶性判断。
            if (abs(r1 - r2) == abs(c1 - c2)) cout << 1 << '\n';
            else
            {
                r1 %= 2, c1 %= 2, r2 %= 2, c2 %= 2;
                if (r1 == c1)
                {
                    if (r2 == c2) cout << 2 << '\n';
                    else cout << "no move\n";
                }
                else
                {
                    if ((r1 == r2) && (c1 == c2) || (r1 + r2 == c1 + c2)) cout << 2 << '\n';
                    else cout << "no move\n";
                }
            }
        }
    }

    return 0;
}
