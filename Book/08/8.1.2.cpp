#include <bits/stdc++.h>

using namespace std;

int n, cnt, ONES;

int dfs(int L, int M, int R)
{
    if (M == ONES) cnt++;
    else
    {
        for (int i = 0; i < n; i++)
            if (((1 << i) & (L | M | R)) == 0)
                dfs((L | (1 << i)) << 1, M | (1 << i), (R | (1 << i)) >> 1);
    }
}

int main(int argc, char *argv[])
{
    clock_t start, finish;

    start = clock();
    while (cin >> n)
    {
        cnt = 0;
        ONES = (1 << n) - 1;
        dfs(0, 0, 0);
        cout << "N = " << n << ": " << cnt << '\n';
    }
    finish = clock();
    cout << (double)(finish - start) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
