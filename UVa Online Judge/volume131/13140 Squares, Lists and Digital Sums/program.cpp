// Squares, Lists and Digital Sums
// UVa ID: 13140
// Verdict: Accepted
// Submission Date: 2022-10-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt = 0;
    long long s = 16, ss;
    while (true)
    {
        ss = s * s;
        int sum = 0;
        while (ss) sum += ss % 10, ss /= 10;
        if (sum == 1 || sum == 4 || sum == 9 || sum == 16 || sum == 25 ||
            sum == 36 || sum == 49 || sum == 64 || sum == 81)
            cnt++;
        else
            cnt = 0;
        if (cnt == 7)
        {
            s -= 6;
            for (int i = 1; i <= 7; i++)
            {
                cout << s << ' ' << s * s << '\n';
                s++;
            }
            break;
        }
        s++;
    }

    return 0;
}
