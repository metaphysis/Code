// Calculator Conundrum
// UVa ID: 11549
// Verdict: Accepted
// Submission Date: 2018-03-18
// UVa Run Time: 0.490s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        long long n, k;
        cin >> n >> k;
        n = pow(10, n);
        set<int> appeared;
        long long maximum = k;
        while (true)
        {
            k *= k;
            while (k >= n) k /= 10;
            if (appeared.find(k) != appeared.end())
                break;
            maximum = max(maximum, k);
            appeared.insert(k);
        }
        cout << maximum << '\n';
    }

    return 0;
}
