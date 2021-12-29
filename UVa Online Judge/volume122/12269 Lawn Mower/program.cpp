// Lawn Mower
// UVa ID: 12269
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int nx, ny;
    double w, xi[1024], yi[1024];
    while (cin >> nx >> ny >> w)
    {
        if (nx == 0) break;
        w /= 2;
        for (int i = 0; i < nx; i++) cin >> xi[i];
        for (int i = 0; i < ny; i++) cin >> yi[i];
        sort(xi, xi + nx);
        sort(yi, yi + ny);
        double lowx = xi[0] - w, highx = xi[0] + w;
        for (int i = 1; i < nx; i++)
        {
            if (xi[i] - w > highx) break;
            highx = xi[i] + w;
        }
        double lowy = yi[0] - w, highy = yi[0] + w;
        for (int i = 1; i < ny; i++)
        {
            if (yi[i] - w > highy) break;
            highy = yi[i] + w;
        }
        int flag = (lowx <= 0 && 75 <= highx) && (lowy <= 0 && 100 <= highy);
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
