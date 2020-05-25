// Dynamic Inversion
// UVa ID: 11990
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net
//
// 参考：https://www.hankcs.com/program/algorithm/uva-11990-inversion.html。

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200010, BLOCK_SIZE = 450, INF = 0x3f3f3f3f;

struct BLOCK { long long cnt, prefixSum; } blocks[BLOCK_SIZE][BLOCK_SIZE];

int n, m, X[MAXN], Y[MAXN];

void updatePrefixSum(int bx, int by)
{
    long long sum = (bx > 0 ? blocks[bx - 1][by].prefixSum : 0);
    for (int i = bx; i < BLOCK_SIZE; i++) {
        sum += blocks[i][by].cnt;
        blocks[i][by].prefixSum = sum;
    }
}

void add(int x, int y)
{
    int bx = x / BLOCK_SIZE, by = y / BLOCK_SIZE;
    blocks[bx][by].cnt++;
    updatePrefixSum(bx, by);
    X[y] = x, Y[x] = y;
}

void remove(int x, int y)
{
    int bx = x / BLOCK_SIZE, by = y / BLOCK_SIZE;
    blocks[bx][by].cnt--;
    updatePrefixSum(bx, by);
    X[y] = INF, Y[x] = INF;
}

long long countSum(int x, int y)
{
    cout << x << ' ' << y << '\n';
    long long cnt = 0;
    int bw = (x + 1) / BLOCK_SIZE,  bh = (y + 1) / BLOCK_SIZE;
    for (int i = 0; i < bh; i++)
        if (bw > 0)
            cnt += blocks[bw - 1][i].prefixSum;
    for (int i = bw * BLOCK_SIZE; i <= x; i++)
    {
        cout << "X: " << i << ' ' << Y[i] << ' ' << y << '\n';
        if (Y[i] <= y)
            cnt++;
    }
    cout << "X: " << cnt << '\n';
    for (int i = bh * BLOCK_SIZE; i <= y; i++)
    {
        cout << "Y: " << i << ' ' << X[i] << ' ' << x << '\n';
        if (X[i] <= x)
            cnt++;
    }
    cout << "Y: " << cnt << '\n';
    return cnt;
}

long long countInversions(int x, int y)
{
    return countSum(x, n - 1) + countSum(n - 1, y) - 2 * countSum(x, y);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m) {
        long long r = 0;
        memset(X, 0x3f, sizeof X);
        memset(Y, 0x3f, sizeof Y);
        memset(blocks, 0, sizeof blocks);
        for (int i = 0, ai; i < n; i++) {
            cin >> ai; ai--;
            add(i, ai);
            r += countInversions(i, ai);
            cout << "A[" << i << "] = " << ai << " Inversions = " << r << '\n';
        }
        for (int i = 0, ai; i < m; i++) {
            cout << r << '\n';
            cin >> ai; --ai;
            r -= countInversions(X[ai], ai);
            remove(X[ai], ai);
        }
    }

    return 0;
}
