// Just Another Easy Problem
// UVa ID: 12938
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    set<int> cache;
    for (int i = 30; i <= 100; i++)
        if (1000 <= i * i && i * i <= 9999)
            cache.insert(i * i);
    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        int a = n / 1000, b = (n % 1000) / 100, c = (n % 100) / 10, d = n % 10;
        int cnt = 0;
        for (int i = 1; i <= 9; i++)
            if (i != a && cache.count(i * 1000 + b * 100 + c * 10 + d))
                cnt++;
        for (int i = 0; i <= 9; i++)
            if (i != b && cache.count(a * 1000 + i * 100 + c * 10 + d))
                cnt++;
        for (int i = 0; i <= 9; i++)
            if (i != c && cache.count(a * 1000 + b * 100 + i * 10 + d))
                cnt++;
        for (int i = 0; i <= 9; i++)
            if (i != d && cache.count(a * 1000 + b * 100 + c * 10 + i))
                cnt++;
        cout << "Case " << cs << ": " << cnt << '\n';
    }
    return 0;
}
