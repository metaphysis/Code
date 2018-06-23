// A Multiplication Game （乘法游戏）
// PC/UVa IDs: 110505/847, Popularity: A, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int N = 0, P = 1;

void dfs(long long n, int flag)
{
    if (n <= 9 && flag == P)
    {
        cout << "Stan wins." << '\n';
        return;
    }
    if (n <= 2 && flag == N)
    {
        cout << "Ollie wins." << '\n';
        return;
    }

    if (flag == P)
        dfs(n / 9 + (n % 9 != 0), N);
    else
        dfs(n / 2 + (n % 2 != 0), P);
}

int main(int ac, char *av[])
{
    long long n;
    while (cin >> n) dfs(n, P);
    return 0;
}
