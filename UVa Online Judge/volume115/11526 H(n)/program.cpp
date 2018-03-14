// H(n)
// UVa ID: 11526
// Verdict: Accepted
// Submission Date: 2018-03-07
// UVa Run Time: 0.160s
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
        if (n <= 0)
        {
            cout << "0\n";
            continue;
        }

        vector<int> r1, r2;
        int divisor = 1, quotient;
        while (true)
        {
            quotient = n / divisor;
            if (divisor > quotient) break;
            if (divisor < quotient)
            {
                r1.push_back(divisor);
                r2.push_back(quotient);
            }
            else r1.push_back(divisor);
            divisor++;
        }
        reverse(r1.begin(), r1.end());
        r2.insert(r2.end(), r1.begin(), r1.end());
        
        long long sum = 0;
        for (int i = 1; i < r2.size(); i++)
            sum += (r2[i - 1] - r2[i]) * (n / r2[i - 1]);
        if (r2.size()) sum += n / r2.back();

        cout << sum << '\n';
    }

    return 0;
}
