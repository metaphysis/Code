// The Last Non-Zero Digit
// UVa ID: 10212
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.980s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int lastDigit[20000010] = {0}, five[20000010] = {0}, two[20000010] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 1; i <= 20000000; i++)
    {
        int x = i;
        while (x % 10 == 0) x /= 10;
        while (x > 1 && x % 5 == 0) five[i]++, x /= 5;
        while (x > 1 && x % 2 == 0) two[i]++, x /= 2;
        lastDigit[i] = x % 10;
    }

    int N, M;
    while (cin >> N >> M)
    {
        int d = 1, cntOfFive = 0, cntOfTwo = 0;
        for (int i = N, j = 1; j <= M; j++, i--)
        {
            d *= lastDigit[i];
            d %= 10;
            cntOfFive += five[i];
            cntOfTwo += two[i];
        }
        if (cntOfFive > cntOfTwo)
            cout << 5 << '\n';
        else
        {
            cntOfTwo -= cntOfFive;
            if (cntOfTwo > 4) cntOfTwo %= 4, d *= 6;
            for (int i = 1; i <= cntOfTwo; i++)
                d *= 2;
            cout << (d % 10) << '\n';
        }
    }

    return 0;
}
