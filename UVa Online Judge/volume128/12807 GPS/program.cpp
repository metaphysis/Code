#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int total;
    cin >> total;
    while (total--) {
        int width, height;
        cin >> width >> height;
        string line;
        getline(cin, line);
        vector<string> mp(height + 2);
        for (int i = 0; i < height + 2; i++) {
            getline(cin, mp[i]);
            if (!mp[i].empty() && mp[i].back() == '\r')
                mp[i].pop_back();
            while ((int)mp[i].size() < width + 2)
                mp[i] += ' ';
        }
        int sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;
        vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
        vector<string> nam = {"east", "south", "west", "north"};
        vector<vector<int>> dis(height, vector<int>(width, -1));
        vector<vector<int>> par(height, vector<int>(width, -1));
        vector<vector<int>> pdir(height, vector<int>(width, -1));
        queue<pair<int, int>> que;
        bool ok = sx >= 0 && sx < width && sy >= 0 && sy < height;
        ok = ok && tx >= 0 && tx < width && ty >= 0 && ty < height;
        ok = ok && mp[sy + 1][sx + 1] == '*' && mp[ty + 1][tx + 1] == '*';
        if (ok) {
            dis[sy][sx] = 0;
            que.push({sx, sy});
            while (!que.empty()) {
                pair<int, int> cur = que.front();
                que.pop();
                int x = cur.first, y = cur.second;
                if (x == tx && y == ty)
                    break;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                        continue;
                    if (mp[ny + 1][nx + 1] != '*' || dis[ny][nx] != -1)
                        continue;
                    dis[ny][nx] = dis[y][x] + 1;
                    par[ny][nx] = y * width + x;
                    pdir[ny][nx] = d;
                    que.push({nx, ny});
                }
            }
            ok = dis[ty][tx] != -1;
        }
        if (!ok) {
            cout << "No route found.\n\n";
            continue;
        }
        if (sx == tx && sy == ty) {
            cout << "You have reached your destination.\n\n";
            continue;
        }
        vector<int> path;
        int x = tx, y = ty;
        while (x != sx || y != sy) {
            path.push_back(pdir[y][x]);
            int val = par[y][x];
            x = val % width;
            y = val / width;
        }
        reverse(path.begin(), path.end());
        int beg = 0;
        cout << "Turn to the " << nam[path[0]] << ".\n";
        while (beg < (int)path.size()) {
            int end = beg + 1;
            while (end < (int)path.size() && path[end] == path[beg])
                end++;
            cout << "Continue " << end - beg << " km.\n";
            if (end < (int)path.size()) {
                int dif = (path[end] - path[end - 1] + 4) % 4;
                if (dif == 1)
                    cout << "Turn right.\n";
                else
                    cout << "Turn left.\n";
            }
            beg = end;
        }
        cout << "You have reached your destination.\n\n";
    }
    return 0;
}
