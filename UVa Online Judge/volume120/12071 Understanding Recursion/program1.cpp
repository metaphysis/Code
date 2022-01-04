// Understanding Recursion
// UVa ID: 12071
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.050s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 40010;

int n, data[MAXN];

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++) cin >> data[i];
        sort(data, data + n);
        long long cnt = 0;
        for (int i = 0, last = 0; i < n; i++)
            if (i && data[i] != data[i - 1])
            {
                cnt += i;
                last = i;
            }
            else cnt += last;
        cout << "Case " << ++cases << ": " << cnt << '\n';
    }
}
