#include <bits/stdc++.h>
using namespace std;

int getGlb(int x, int y, const vector<vector<unsigned long long>>& low, const vector<int>& pos) {
    int ans = -1, words = low[x].size();
    for (int i = 0; i < words; ++i) {
        unsigned long long bits = low[x][i] & low[y][i];
        while (bits) {
            int bit = __builtin_ctzll(bits);
            int z = (i << 6) + bit;
            if (ans == -1 || pos[z] > pos[ans]) ans = z;
            bits &= bits - 1;
        }
    }
    return ans;
}

int solve() {
    int t;
    cin >> t;
    while (t--) {
        int l, r, u, d, a;
        cin >> l >> r >> u >> d >> a;
        vector<vector<int>> graph(l);
        vector<int> inDeg(l, 0);
        for (int i = 0; i < r; ++i) {
            int x, y;
            cin >> x >> y;
            --x;
            --y;
            if (x == y) continue;
            graph[x].push_back(y);
            ++inDeg[y];
        }
        vector<int> ord;
        queue<int> que;
        for (int i = 0; i < l; ++i) {
            if (inDeg[i] == 0) que.push(i);
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            ord.push_back(x);
            for (int y : graph[x]) {
                --inDeg[y];
                if (inDeg[y] == 0) que.push(y);
            }
        }
        vector<int> pos(l);
        for (int i = 0; i < l; ++i) pos[ord[i]] = i;
        int words = (l + 63) >> 6;
        vector<vector<unsigned long long>> reach(l, vector<unsigned long long>(words, 0));
        for (int i = l - 1; i >= 0; --i) {
            int x = ord[i];
            reach[x][x >> 6] |= 1ULL << (x & 63);
            for (int y : graph[x]) {
                for (int j = 0; j < words; ++j) reach[x][j] |= reach[y][j];
            }
        }
        vector<vector<unsigned long long>> low(l, vector<unsigned long long>(words, 0));
        for (int x = 0; x < l; ++x) {
            for (int i = 0; i < words; ++i) {
                unsigned long long bits = reach[x][i];
                while (bits) {
                    int bit = __builtin_ctzll(bits);
                    int y = (i << 6) + bit;
                    low[y][x >> 6] |= 1ULL << (x & 63);
                    bits &= bits - 1;
                }
            }
        }
        vector<int> users(u), docs(d);
        for (int i = 0; i < u; ++i) {
            cin >> users[i];
            --users[i];
        }
        for (int i = 0; i < d; ++i) {
            cin >> docs[i];
            --docs[i];
        }
        for (int i = 0; i < a; ++i) {
            int user, document;
            string action;
            cin >> user >> action >> document;
            --user;
            --document;
            int value = getGlb(users[user], docs[document], low, pos);
            if (action == "reads") {
                users[user] = value;
                cout << value + 1 << '\n';
            } else {
                docs[document] = value;
                cout << value + 1 << '\n';
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
