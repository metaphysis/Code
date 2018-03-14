// Zeros and Ones
// UVa ID: 10324
// Verdict: Accepted
// Submission Date: 2017-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    int queries, begin, end, cases = 0;
    int sum[1000010];

    while (cin >> line)
    {
        sum[0] = 0;
        for (int i = 0; i < line.length(); i++)
            sum[i + 1] = sum[i] + line[i] - '0';
        sum[line.length() + 1] = sum[line.length()];
            
        cout << "Case " << ++ cases << ":\n";

        cin >> queries;
        for (int i = 1; i <= queries; i++)
        {
            cin >> begin >> end;
            if (begin > end) swap(begin, end);
            int temp = sum[end + 1] - sum[begin];
            if (temp == 0 || temp == (end - begin + 1)) cout << "Yes\n";
            else cout << "No\n";
        }
    }

    return 0;
}
