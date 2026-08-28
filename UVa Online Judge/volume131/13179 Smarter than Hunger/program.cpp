#include <bits/stdc++.h>
using namespace std;

struct Pos {
    int row, col;
};

vector<pair<int, int> > dp[105][105];
Pos pos[105];

int getDis(int a, int b) {
    return abs(pos[a].row - pos[b].row) + abs(pos[a].col - pos[b].col);
}

void addLab(vector<pair<int, int> > &vec, int tim, int oth) {
    for (const pair<int, int> &p : vec)
        if (p.first <= tim && p.second <= oth)
            return;
    for (int i = 0; i < (int)vec.size();) {
        if (tim <= vec[i].first && oth <= vec[i].second)
            vec.erase(vec.begin() + i);
        else
            i++;
    }
    vec.push_back(make_pair(tim, oth));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, n;
    while (cin >> r >> c) {
        cin >> n;
        for (int i = 0; i < 105; i++)
            for (int j = 0; j < 105; j++)
                dp[i][j].clear();
        pos[0] = {1, 1};
        for (int i = 1; i <= n; i++)
            cin >> pos[i].row >> pos[i].col;
        pos[n + 1] = {r, c};
        addLab(dp[0][0], 0, 0);
        for (int k = 0; k < n; k++) {
            for (int j = 0; j <= k; j++) {
                for (const pair<int, int> &p : dp[k][j]) {
                    int tim = p.first, oth = p.second;
                    int nxt = k + 1;
                    addLab(dp[nxt][j], tim + getDis(k, nxt), oth);
                    addLab(dp[nxt][k], max(tim, oth + getDis(j, nxt)), tim);
                }
            }
        }
        int ans = INT_MAX;
        for (int j = 0; j <= n; j++) {
            for (const pair<int, int> &p : dp[n][j])
                ans = min(ans, max(p.first + getDis(n, n + 1), p.second + getDis(j, n + 1)) + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
