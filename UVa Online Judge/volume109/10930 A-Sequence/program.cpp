// A-Sequence
// UVa ID: 10930
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, number[32], cases = 0, sum[30010];
    while (cin >> n)
    {
        cout << "Case #" << ++cases << ":";
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            cin >> number[i];
            cout << ' ' << number[i];
            if (i && number[i] <= number[i - 1])
                flag = false;
        }
        cout << '\n';
        
        if (flag)
        {
            memset(sum, 0, sizeof(sum));
            for (int i = 0; i < n; i++)
            {
                for (int j = 30000; j >= 0; j--)
                    if (sum[j])
                        sum[j + number[i]] = 1;
                for (int j = i; j < n; j++)
                    if (sum[number[j]])
                    {
                        flag = false;
                        break;
                    }
                if (!flag) break;
                sum[number[i]] = 1;
            }
        }
        
        if (flag) cout << "This is an A-sequence.\n";
        else cout << "This is not an A-sequence.\n";
    }
    return 0;
}
