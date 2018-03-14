// Brick Game
// UVa ID: 11875
// Verdict: Accepted
// Submission Date: 2018-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, age[12];
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> age[i];
        sort(age, age + n);
        cout << "Case " << c << ": " << age[n / 2] << '\n';
    }

    return 0;
}
