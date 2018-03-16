// Fi-binary Number
// UVa ID: 11089
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fibonacci[46] = {0, 1, 1}, total[46] = {0, 1, 2};
    for (int i = 3; i <= 45; i++)
    {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        total[i] = total[i - 1] + fibonacci[i];
    }
    
    int cases;
    long long n;

    cin >> cases;
    while (cases--)
    {
        cin >> n;
        bitset<64> binary(0);
        while (n > 0)
        {
            int k = lower_bound(total, total + 46, n) - total;
            binary.set(k - 1);
            n = n - total[k - 1] - 1;
        }
        string b = binary.to_string();
        while (b.front() == '0') b.erase(b.begin());
        cout << b << '\n';
    }

    return 0;
}
