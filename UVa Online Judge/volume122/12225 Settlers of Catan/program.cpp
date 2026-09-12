#include <bits/stdc++.h>  
using namespace std;  
  
int main() {  
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);  
    int c, maxN = 10000, id;  
    cin >> c;  
    vector<int> query(c), answer(maxN + 1), cnt(6, 0);  
    for (int i = 0; i < c; i++) cin >> query[i];  
    int dx[6] = {1, 0, -1, -1, 0, 1}, dy[6] = {0, 1, 1, 0, -1, -1};  
    map<pair<int, int>, int> tile;  
    tile[{0, 0}] = answer[1] = cnt[1] = id = 1;  
    int basex = 0, basey = 0;  
    for (int r = 1; id < maxN; r++) {  
        basex += dx[5], basey += dy[5];  
        vector<pair<int, int>> tmp;  
        tmp.push_back({basex + dx[1], basey + dy[1]});  
        for (int i = 0; i < 6; i++) tmp.push_back({dx[i] * r, dy[i] * r});  
        for (int i = 0, d = 1; i < tmp.size() - 1; i++, d++) {  
            int x1 = tmp[i].first, y1 = tmp[i].second;  
            int x2 = tmp[i + 1].first, y2 = tmp[i + 1].second;  
            while (id < maxN) {  
                if (tile.find({x1, y1}) == tile.end()) {  
                    bool used[6] = {};  
                    for (int k = 0; k < 6; k++) {  
                        int nx = x1 + dx[k], ny = y1 + dy[k];  
                        auto it = tile.find({nx, ny});  
                        if (it != tile.end()) used[it->second] = true;  
                    }  
                    int color = 0;  
                    for (int k = 1; k <= 5; k++) {  
                        if (!used[k] && (color == 0 || cnt[k] < cnt[color])) color = k;  
                    }  
                    tile[{x1, y1}] = color;  
                    answer[++id] = color;  
                    cnt[color]++;  
                }  
                if (x1 == x2 && y1 == y2) break;  
                x1 += dx[d % 6], y1 += dy[d % 6];  
            }  
        }  
    }  
    for (int i = 0; i < c; i++) cout << answer[query[i]] << '\n';  
    return 0;  
}
