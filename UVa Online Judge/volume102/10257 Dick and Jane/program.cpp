// Dick and Jane
// UVa ID: 10257
// Verdict: Accepted
// Submission Date: 2018-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// It is a weird problem!

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int s, p, y, j;
    while (cin >> s >> p >> y >> j)
    {
        int turtle = (12 + j - p - y) / 3;
        int cat = (12 + j - s - turtle) / 2;
        int dog = (12 + j - cat - turtle);
        cout << dog << ' ' << cat << ' ' << turtle << '\n';
    }

    return 0;
}
