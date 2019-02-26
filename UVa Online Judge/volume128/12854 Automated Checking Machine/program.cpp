// Automated Checking Machine
// UVa ID: 12854
// Verdict: Accepted
// Submission Date: 2019-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s1, s2;
    while (getline(cin, s1), s1.length() > 0)
    {
        getline(cin, s2);
        int n1 = 0, n2 = 0;
        for (int i = 0; i < s1.length(); i++)
            if (s1[i] == '0' || s1[i] == '1')
                n1 = n1 * 10 + s1[i] - '0';
        for (int i = 0; i < s2.length(); i++)
            if (s2[i] == '0' || s2[i] == '1')
                n2 = n2 * 10 + s2[i] - '0';
        cout << (n1 + n2 == 11111 ? 'Y' : 'N') << '\n';       
    }

    return 0;
}
