// ASCII Diamond
// UVa ID: 12155
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, row1, row2, col1, col2;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ":\n";
        cin >> row1 >> col1 >> row2 >> col2;
        for (int i = row1; i <= row2; i++)
        {
            for (int j = col1; j <= col2; j++)
            {
                int r = i % (2 * n - 1), c = j % (2 * n - 1);
                int rowDiff = r - (n - 1), clnDiff = c - (n - 1);
                if (abs(rowDiff) + abs(clnDiff) >= n)
                    cout << '.';
                else
                    cout << (char)('a' + ((abs(rowDiff) % 26) + (abs(clnDiff) % 26)) % 26);
            }
            cout << '\n';
        }
    }

    return 0;
}
