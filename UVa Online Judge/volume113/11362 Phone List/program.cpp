// Phone List
// UVa ID: 11362
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        vector<string> phone(n);
        for (int i = 0; i < n; i++)
            cin >> phone[i];
        sort(phone.begin(), phone.end());
        bool flag = true;
        for (int i = 0; i < phone.size() - 1; i++)
        {
            bool same = true;
            for (int j = 0; j < phone[i].length(); j++)
                if (phone[i][j] != phone[i + 1][j])
                {
                    same = false;
                    break;
                }
            if (same)
            {
                flag = false;
                break;
            }
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }

    return 0;
}
