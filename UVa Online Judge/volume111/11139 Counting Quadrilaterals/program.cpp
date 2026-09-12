#include <bits/stdc++.h>  
using namespace std;  
  
#define N 123  
  
int f[N][N][N], g[N][N], n;  
long long c[N][N];  
  
void initialize() {  
    for (int i = 0; i < N; ++i) for (int j = i; j < N; ++j) g[i][j] = g[j][i] = __gcd(i, j);  
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {  
        f[i][j][0] = 0;  
        for (int k = 1; k < N; ++k) f[i][j][k] = f[i][j][k - 1] + (i ? (k * j % i ? k * j / i : k * j / i - 1) : 0);  
    }  
    for (int x = 1; x < N; ++x) for (int y = x; y < N; ++y) {  
        long long t = 1LL * (x + 1) * (y + 1) - g[x][y] - 1, cc = t * t / 2 - 1 + (x - 1) * (x - 2) + (y - 1) * (y - 2) + 1LL * (x - 1) * (y - 1) * (6 * (x + y) - 8) + 1LL * (x - 1) * (x - 1) * (y - 1) * (y - 1);  
        for (int x1 = 1; x1 <= x; ++x1) {  
            int y1 = y * x1;  
            y1 = y1 % x ? y1 / x : y1 / x - 1;  
            while (y1 >= 0) {  
                cc += 2LL * (f[y1][x1][y1] - f[y - y1][x - x1][y1] - 1LL * g[y - y1][x - x1] * y1 / (y - y1));  
                cc += 2LL * (f[x - x1][y - y1][x - x1] - f[x1][y1][x - x1] - 1LL * g[x1][y1] * (x - x1) / x1);  
                cc += 6LL * (x1 * y - x * y1 + 2 - g[x1][y1] - g[x - x1][y - y1] - g[x][y]);  
                --y1;  
            }  
        }  
        for (int x1 = 1; x1 < x; ++x1) {  
            cc += 1LL * (x - 2) * (y - 1) + 2 - g[x1][y] - g[x - x1][y];  
            cc += 3LL * (x * y + 2 - x - g[x1][y] - g[x - x1][y]);  
        }  
        for (int y1 = 1; y1 < y; ++y1) {  
            cc += 1LL * (x - 1) * (y - 2) + 2 - g[x][y1] - g[x][y - y1];  
            cc += 3LL * (x * y + 2 - y - g[x][y1] - g[x][y - y1]);  
        }  
        for (int x1 = 1; x1 < x; ++x1) for (int y1 = 1; y1 < y; ++y1) {  
            cc += 2LL * (x * y + x1 * y1 + 6 - 2 * x - 2 * y - g[x1][y] - g[x][y1] - g[x - x1][y - y1]);  
            cc += 6LL * (x * y - x1 * y1 + 2 - g[x1][y] - g[x][y1] - g[x - x1][y - y1]);  
        }  
        c[x][y] = c[y][x] = cc;  
    }  
}  
  
void solve() {  
    long long cnt = 0;  
    for (int x = 1; x <= n; ++x) for (int y = 1; y <= n; ++y) cnt += 1LL * (n + 1 - x) * (n + 1 - y) * c[x][y];  
    cout << n << " " << cnt << endl;  
}  
  
int main() {  
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);  
    initialize();  
    while (cin >> n && n) solve();  
    return 0;  
}
