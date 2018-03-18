// Generate Random Numbers
// UVa ID: 11634
// Verdict: Accepted
// Submission Date: 2018-03-18
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        set<int> appeared;
        while (true)
        {
            if (appeared.find(n) != appeared.end())
                break;
            appeared.insert(n);
            n *= n;
            n /= 100;
            n %= 10000;
            
        }
        cout << appeared.size() << '\n';
    }

    return 0;
}
