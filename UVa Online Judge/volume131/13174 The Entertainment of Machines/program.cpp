#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[2], fail, cnt;
    Node() {
        nxt[0] = nxt[1] = -1;
        fail = cnt = 0;
    }
};

void insertWord(vector<Node>& ac, const string& word, vector<int>& endPos, int id) {
    int u = 0;
    for (char ch : word) {
        int bit = ch - '0';
        if (ac[u].nxt[bit] == -1) {
            ac[u].nxt[bit] = ac.size();
            ac.emplace_back();
        }
        u = ac[u].nxt[bit];
    }
    endPos[id] = u;
}

void buildAc(vector<Node>& ac, vector<int>& order) {
    vector<int> que;
    int head = 0;
    for (int bit = 0; bit < 2; ++bit) {
        int v = ac[0].nxt[bit];
        if (v == -1) ac[0].nxt[bit] = 0;
        else {
            ac[v].fail = 0;
            que.push_back(v);
        }
    }
    while (head < (int)que.size()) {
        int u = que[head++];
        order.push_back(u);
        for (int bit = 0; bit < 2; ++bit) {
            int v = ac[u].nxt[bit];
            if (v == -1) ac[u].nxt[bit] = ac[ac[u].fail].nxt[bit];
            else {
                ac[v].fail = ac[ac[u].fail].nxt[bit];
                que.push_back(v);
            }
        }
    }
}

void scanLine(const vector<string>& grid, vector<Node>& ac, int x, int y, int dx, int dy) {
    int sx = grid[0].size(), sy = grid.size(), u = 0;
    while (x >= 0 && x < sx && y >= 0 && y < sy) {
        u = ac[u].nxt[grid[y][x] - '0'];
        ++ac[u].cnt;
        x += dx;
        y += dy;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int sx, sy;
    while (cin >> sx >> sy) {
        vector<string> grid(sy);
        int oneCnt[2] = {0, 0};
        for (int y = 0; y < sy; ++y) {
            cin >> grid[y];
            for (char ch : grid[y]) ++oneCnt[ch - '0'];
        }
        int n;
        cin >> n;
        vector<string> words(n);
        vector<int> endPos(n);
        vector<Node> ac(1);
        for (int i = 0; i < n; ++i) {
            cin >> words[i];
            insertWord(ac, words[i], endPos, i);
        }
        vector<int> order;
        buildAc(ac, order);
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                for (int y = 0; y < sy; ++y) {
                    for (int x = 0; x < sx; ++x) {
                        int px = x - dx, py = y - dy;
                        if (px < 0 || px >= sx || py < 0 || py >= sy) scanLine(grid, ac, x, y, dx, dy);
                    }
                }
            }
        }
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            ac[ac[u].fail].cnt += ac[u].cnt;
        }
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return words[a] < words[b];
        });
        for (int id : ids) {
            int ans;
            if (words[id].size() == 1) ans = oneCnt[words[id][0] - '0'];
            else ans = ac[endPos[id]].cnt;
            if (ans > 0) cout << words[id] << ' ' << ans << '\n';
        }
        cout << "---\n";
    }
    return 0;
}
