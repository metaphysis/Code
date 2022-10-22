// Headshot
// UVa ID: 1636
// Verdict: Accepted
// Submission Date: 2022-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        int s1 = 0, d1 = 0, s2 = 0, d2 = 0;
        int L = (int)line.length();
        for (int i = 0, j = 1; i < line.length(); i++, j++)
        {
            j %= L;
            if (line[i] == '0')
            {
                s2++;
                if (line[j] == '0') s1++;
                else d1++;
            }
            else d2++;
        }
        d1 += s1;
        d2 += s2;
        s1 *= d2;
        s2 *= d1;
        if (s1 > s2 ) cout << "SHOOT";
        else if (s1 < s2 ) cout << "ROTATE";
        else cout << "EQUAL";
        cout << '\n';
    }

    return 0;
}
