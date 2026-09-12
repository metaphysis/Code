#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int r, c, n;
        cin >> r >> c >> n;
        vector<vector<int>> ans(r, vector<int>(c, 0));
        while (n--) {
            int x, y, s, d = 0, len = 1, step = 0;
            char ch;
            cin >> x >> y >> ch >> s;
            --x;
            --y;
            if (ch == 'N') d = 0;
            else if (ch == 'E') d = 1;
            else if (ch == 'S') d = 2;
            else d = 3;
            int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
            bool stop = false;
            while (!stop) {
                for (int k = 0; k < 2 && !stop; ++k) {
                    for (int i = 0; i < len; ++i) {
                        ++ans[x][y];
                        if (step == s) {
                            stop = true;
                            break;
                        }
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
                            stop = true;
                            break;
                        }
                        x = nx;
                        y = ny;
                        ++step;
                    }
                    d = (d + 1) % 4;
                }
                ++len;
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (j) cout << ' ';
                cout << ans[i][j];
            }
            cout << '\n';
        }
        cout << "---\n";
    }
    return 0;
}
