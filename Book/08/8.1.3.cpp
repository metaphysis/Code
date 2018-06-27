#include <bits/stdc++.h>

using namespace std;

int n, cnt, ONES;

void dfs(int L, int M, int R)
{
    int empty, cln;
    if (M != ONES) {
        empty = ONES & (~(L | M | R));
        while (empty) {
            cln = empty & (~empty + 1);
            empty ^= cln;
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
        ONES = (1 << n) - 1;
        dfs(0, 0, 0);
        cout << "N = " << n << ": " << cnt << '\n';
    }
    finish = clock();
    cout << (double)(finish - start) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
