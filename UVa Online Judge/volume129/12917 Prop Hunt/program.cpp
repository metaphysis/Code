// Prop Hunt
// UVa ID: 12917
// Verdict: Accepted
// Submission Date: 2019-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int P, H, O;
    while (cin >> P >> H >> O)
    {
        if (H > (O - P)) cout << "Hunters win!\n";
        else cout << "Props win!\n";
    }
    return 0;
}
