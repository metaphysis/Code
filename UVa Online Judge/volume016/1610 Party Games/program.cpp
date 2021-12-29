// Party Games
// UVa ID: 1610
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    string name[1024];
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> name[i];
        sort(name, name + n);
        string s1 = name[(n - 1) / 2], s2 = name[n / 2];
        string s3;
        for (int i = 0; i < s1.size(); i++)
        {
            s3 += s1[i];
            if (s1 <= s3 && s3 < s2) break;
            s3.pop_back();
            if (s1[i] != 'Z')
            {
                s3 += (char)(s1[i] + 1);
                if (s1 <= s3 && s3 < s2) break;
                s3.pop_back();
            }
            s3 += s1[i];
        }
        cout << s3 << '\n';
    }
    return 0;
}
