#include <bits/stdc++.h>

using namespace std;

int n, cnt, N_ONES;

void dfs(int L, int M, int R)
{
    int available, cln;
    if (M != N_ONES) {
        available = N_ONES & (~(L | M | R));
        while (available) {
            cln = available & (~available + 1);
            available ^= cln;
            dfs((L | cln) << 1, M | cln, (R | cln) >> 1);
        }
    }
    else cnt++;
}

int main(int argc, char *argv[])
{
    clock_t start, finish;

    start = clock();
    while (cin >> n)
    {
        cnt = 0;
        N_ONES = (1 << n) - 1;
        dfs(0, 0, 0);
        cout << "N = " << n << ": " << cnt << '\n';
    }
    finish = clock();
    cout << (double)(finish - start) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
