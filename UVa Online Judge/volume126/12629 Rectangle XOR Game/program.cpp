#include <bits/stdc++.h>
using namespace std;

const int maxN = 100;
const int maxXor = 1024;

int sg[maxN + 1][maxN + 1];
int pre[maxN + 1][maxN + 1];
int ways[maxN + 1][maxN + 1][maxXor];
int board[maxN][maxN];

void init() {
    memset(sg, 0, sizeof(sg));
    memset(pre, 0, sizeof(pre));
    memset(ways, 0, sizeof(ways));
    for (int i = 1; i <= maxN; i++) {
        for (int j = 1; j <= maxN; j++) {
            pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1];
            for (int a = 1; a <= i; a++) {
                for (int b = 1; b <= j; b++) {
                    int value = pre[i][j] ^ pre[i - a][j] ^ pre[i][j - b] ^ pre[i - a][j - b];
                    ways[i][j][value]++;
                }
            }
            for (int value = 0; value < maxXor; value++)
                if (!ways[i][j][value]) {
                    sg[i][j] = value;
                    break;
                }
            pre[i][j] ^= sg[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int n, m;
    while (cin >> n >> m) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> board[i][j];
                if (board[i][j]) ans ^= sg[n - i][m - j];
            }
        }
        if (!ans) {
            cout << "No\n";
            continue;
        }
        int count = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j])
                    count += ways[n - i][m - j][sg[n - i][m - j] ^ ans];
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < m && !found; j++) {
                if (!board[i][j]) continue;
                int x = n - i, y = m - j;
                for (int a = 1; a <= x && !found; a++) {
                    for (int b = 1; b <= y; b++) {
                        int value = pre[x][y] ^ pre[x - a][y] ^ pre[x][y - b] ^ pre[x - a][y - b];
                        if (value == ans) {
                            x1 = i + 1;
                            y1 = j + 1;
                            x2 = i + a;
                            y2 = j + b;
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        cout << count << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    }
    return 0;
}
