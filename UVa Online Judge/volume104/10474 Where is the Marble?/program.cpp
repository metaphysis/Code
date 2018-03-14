// Where is the Marble?
// UVa ID: 10474
// Verdict: Accepted
// Submission Date: 2017-11-28
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, q, cases = 0;
    int numbers[1000010];

    while (cin >> n >> q)
    {
        if (n == 0 && q == 0) break;

        for (int i = 0; i < n; i++)
            cin >> numbers[i];
        sort(numbers, numbers + n);

        cout << "CASE# " << ++cases << ":\n";
        for (int i = 1, j, k; i <= q; i++)
        {
            cin >> j;

            if (!binary_search(numbers, numbers + n, j)) cout << j << " not found\n";
            else
            {
                k = lower_bound(numbers, numbers + n, j) - numbers;
                cout << j << " found at " << (k + 1) << '\n';
            }
        }
    }

    return 0;
}
