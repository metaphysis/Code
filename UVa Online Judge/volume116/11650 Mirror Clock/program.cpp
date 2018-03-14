// Mirror Clock
// UVa ID: 11650
// Verdict: Accepted
// Submission Date: 2017-12-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, HH, MM;
    char seperator;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> HH >> seperator >> MM;
        
        if (MM == 0) HH = 12 - HH;
        else HH = 11 - HH;
        if (HH <= 0) HH += 12;
        MM = (60 - MM) % 60;

        cout << setw(2) << setfill('0') << HH;
        cout << ':';
        cout << setw(2) << setfill('0') << MM << '\n';
    }

    return 0;
}
