#include <bits/stdc++.h>
using namespace std;

vector<string> pcs;
int board[16], vis[16], cnt;
string ans[4][4];

bool isValid(const vector<string> &cur) {
    set<string> st;
    if (cur.size() != 16) return false;
    for (string s : cur) {
        if (s.size() != 4) return false;
        for (char c : s)
            if (c < '0' || c > '9') return false;
        if (!st.insert(s).second) return false;
    }
    return true;
}

void dfs(int pos) {
    if (cnt >= 2) return;
    if (pos == 16) {
        cnt++;
        if (cnt == 1)
            for (int i = 0; i < 16; i++)
                ans[i / 4][i % 4] = pcs[board[i]];
        return;
    }
    int row = pos / 4, col = pos % 4;
    for (int i = 0; i < 16; i++) {
        if (vis[i]) continue;
        string &s = pcs[i];
        if (col > 0 && pcs[board[pos - 1]][0] != s[2]) continue;
        if (row > 0 && pcs[board[pos - 4]][3] != s[1]) continue;
        board[pos] = i;
        vis[i] = 1;
        dfs(pos + 1);
        vis[i] = 0;
        if (cnt >= 2) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<string> > cases;
    vector<string> cur;
    string line;
    while (getline(cin, line)) {
        bool empty = true;
        for (char c : line)
            if (!isspace((unsigned char)c)) empty = false;
        if (empty) {
            if (!cur.empty()) {
                cases.push_back(cur);
                cur.clear();
            }
            continue;
        }
        stringstream ss(line);
        string s;
        while (ss >> s) cur.push_back(s);
    }
    if (!cur.empty()) cases.push_back(cur);
    for (int k = 0; k < (int)cases.size(); k++) {
        if (k > 0) cout << '\n';
        if (!isValid(cases[k])) {
            cout << "0\n";
            continue;
        }
        pcs = cases[k];
        memset(board, 0, sizeof(board));
        memset(vis, 0, sizeof(vis));
        cnt = 0;
        dfs(0);
        if (cnt == 0) {
            cout << "1\n";
        } else if (cnt >= 2) {
            cout << "3\n";
        } else {
            cout << "2\n";
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (j > 0) cout << ' ';
                    cout << ans[i][j];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
