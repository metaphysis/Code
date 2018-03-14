// Schedule of a Married Man
// UVa ID: 12136
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

    int cases;
    int starth1, startm1, endh1, endm1;
    int starth2, startm2, endh2, endm2;
    char seperator;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> starth1 >> seperator >> startm1;
        cin >> endh1 >> seperator >> endm1;
        cin >> starth2 >> seperator >> startm2;
        cin >> endh2 >> seperator >> endm2;
        
        int tm1 = starth1 * 60 + startm1;
        int tm2 = endh1 * 60 + endm1;
        int tm3 = starth2 * 60 + startm2;
        int tm4 = endh2 * 60 + endm2;
        
        cout << "Case " << c << ": ";
        if (tm1 >= tm3 && tm1 <= tm4 || tm2 >= tm3 && tm2 <= tm4 ||
            tm3 >= tm1 && tm3 <= tm2 || tm4 >= tm1 && tm4 <= tm2)
            cout << "Mrs Meeting\n";
        else
            cout << "Hits Meeting\n";
    }

    return 0;
}
