// Abnormal 89's
// UVa ID: 11888
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        
        if (line.length() == 1)
        {
            cout << "palindrome\n";
            continue;
        }

        bool printed = false;
        for (int i = 0; i < line.length() - 1; i++)
        {
            if (line[i] == line[0] && line[i + 1] == line.back())
            {
                bool same = true;
                for (int j = 0, k = i; j <= k; j++, k--)
                    if (line[j] != line[k])
                    {
                        same = false;
                        break;
                    }
                if (!same) continue;
                for (int j = i + 1, k = line.length() - 1; j <= k; j++, k--)
                    if (line[j] != line[k])
                    {
                        same = false;
                        break;
                    }
                if (same)
                {
                    cout << "alindrome\n";
                    printed = true;
                    break;
                }
            }
        }
        
        if (printed) continue;
        
        bool flag = true;
        for (int i = 0, j = line.length() - 1; i <= j; i++, j--)
            if (line[i] != line[j])
            {
                flag = false;
                break;
            }
            
        if (flag)
            cout << "palindrome\n";
        else
            cout << "simple\n";
    }

    return 0;
}
