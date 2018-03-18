// Powers Et Al.
// UVa ID: 10515
// Verdict: Accepted
// Submission Date: 2018-03-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int table[10][10] = {
    {1, 0},
    {1, 1},
    {4, 2, 4, 8, 6},
    {4, 3, 9, 7, 1},
    {2, 4, 6},
    {1, 5},
    {1, 6},
    {4, 7, 9, 3, 1},
    {4, 8, 4, 2, 6},
    {2, 9, 1}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string m, n;
    while (cin >> m >> n)
    {
        if (m == "0" && n == "0")
            break;
        if (n == "0")
        {
            cout << "1\n";
            continue;
        }
        int mm = m.back() - '0';
        if (mm == 0 || mm == 1 || mm == 5 || mm == 6)
        {
            cout << mm << '\n';
            continue;
        }
        int nn = 0;
        for (auto d : n)
            nn = (nn * 10 + d - '0') % table[mm][0];
        if (nn == 0) nn = table[mm][0];
        cout << table[mm][nn] << '\n';
    }

    return 0;
}
