// Deck
// UVa ID: 651
// Verdict: Accepted
// Submission Date: 2017-05-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout.setf(ios::fixed);
    cout.precision(3);

    cout << "# Cards Overhang\n";
    
    double overhang[100000] = {0.0};
    
    for (int i = 1; i <= 99999; i++)
        overhang[i] = overhang[i - 1] + 1.0 / (double)(2 * i);
    
    int cards;
    while (cin >> cards)
    {
        cout << setw(5) << right << cards;
        cout << setw(10) << right << overhang[cards] << '\n';
    }
    
    return 0;
}
