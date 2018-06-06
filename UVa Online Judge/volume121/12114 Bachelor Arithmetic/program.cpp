// Bachelor Arithmetic
// UVa ID: 12114
// Verdict: Accepted
// Submission Date: 2018-06-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    long long B, S, BB, SS;
    while (cin >> B >> S, B > 0)
    {
        cout << "Case " << ++cases << ": ";
        BB = B - 1, SS = S - 1;
        if (BB == 0) cout << ":-\\\n";
        else if (SS == 0) cout << ":-(\n";
        else
        {
            if (S > B) S = B;
            if (SS > BB) SS = BB;
            if (S * BB == SS * B) cout << ":-|\n";
            else if (S * BB > SS * B) cout << ":-(\n";
            else cout << ":-)\n";
        }
    }

    return 0;
}
