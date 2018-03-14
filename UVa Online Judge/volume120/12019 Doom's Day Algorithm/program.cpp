// Doom's Day Algorithm
// UVa ID: 12019
// Verdict: Accepted
// Submission Date: 2017-12-28
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string weekday[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, M, D;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> M >> D;
        if (M == 4)
        {
            if (D == 4)
            {
                cout << weekday[0] << '\n';
            }
            else if (D < 4)
            {
                cout << weekday[7 - (4 - D)] << '\n';
            }
            else
            {
                cout << weekday[(D - 4) % 7] << '\n';
            }
        }
        else if (M < 4)
        {
            int T = daysInMonth[M - 1] - D;
            for (int i = M + 1; i < 4; i++) T += daysInMonth[i - 1];
            T += 4;
            cout << weekday[(7 - T % 7) % 7] << '\n';
        }
        else
        {
            int T = 26;
            for (int i = 5; i < M; i++) T += daysInMonth[i - 1];
            T += D;
            cout << weekday[T % 7] << '\n';
        }
    }

    return 0;
}
