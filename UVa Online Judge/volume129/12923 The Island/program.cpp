#include <bits/stdc++.h>
using namespace std;

const int maxN = 105;
const int inf = 0x3f3f3f3f;

int n, w[maxN][maxN], lx[maxN], ly[maxN], matchY[maxN], slack[maxN];
bool visX[maxN], visY[maxN];

bool findPath(int x) {
    visX[x] = true;
    for (int y = 1; y <= n; y++) {
        if (visY[y]) continue;
        int gap = lx[x] + ly[y] - w[x][y];
        if (gap == 0) {
            visY[y] = true;
            if (!matchY[y] || findPath(matchY[y])) {
                matchY[y] = x;
                return true;
            }
        } else if (slack[y] > gap) {
            slack[y] = gap;
        }
    }
    return false;
}

int kmSolve() {
    fill(lx + 1, lx + n + 1, 0);
    fill(ly + 1, ly + n + 1, 0);
    fill(matchY + 1, matchY + n + 1, 0);
    for (int x = 1; x <= n; x++) {
        lx[x] = w[x][1];
        for (int y = 2; y <= n; y++) lx[x] = max(lx[x], w[x][y]);
    }
    for (int x = 1; x <= n; x++) {
        fill(slack + 1, slack + n + 1, inf);
        while (true) {
            fill(visX + 1, visX + n + 1, false);
            fill(visY + 1, visY + n + 1, false);
            if (findPath(x)) break;
            int d = inf;
            for (int y = 1; y <= n; y++) if (!visY[y]) d = min(d, slack[y]);
            for (int i = 1; i <= n; i++) if (visX[i]) lx[i] -= d;
            for (int y = 1; y <= n; y++) {
                if (visY[y]) ly[y] += d;
                else slack[y] -= d;
            }
        }
    }
    int ans = 0;
    for (int y = 1; y <= n; y++) ans += w[matchY[y]][y];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> w[i][j];
        cout << kmSolve() << '\n';
    }
    return 0;
}
