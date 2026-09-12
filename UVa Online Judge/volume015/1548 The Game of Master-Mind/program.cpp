#include <bits/stdc++.h>
using namespace std;

int p, c, m;
vector<vector<int>> seq, freq;
vector<int> need, tar, mat, def, blk, cnt, cur, ans, dom;

bool dfs(int pos) {
    int rem = p - pos;
    for (int i = 0; i < m; i++) {
        if (blk[i] > tar[i]) return false;
        if (blk[i] + rem < tar[i]) return false;
        if (mat[i] > need[i]) return false;
        if (mat[i] + min(rem, def[i]) < need[i]) return false;
    }
    if (pos == p) {
        for (int i = 0; i < m; i++)
            if (blk[i] != tar[i] || mat[i] != need[i]) return false;
        ans = cur;
        return true;
    }
    for (int x : dom) {
        int old = cnt[x];
        cnt[x]++;
        cur[pos] = x;
        for (int i = 0; i < m; i++) {
            if (old < freq[i][x]) {
                mat[i]++;
                def[i]--;
            }
            if (seq[i][pos] == x) blk[i]++;
        }
        if (dfs(pos + 1)) return true;
        for (int i = 0; i < m; i++) {
            if (old < freq[i][x]) {
                mat[i]--;
                def[i]++;
            }
            if (seq[i][pos] == x) blk[i]--;
        }
        cnt[x]--;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> p >> c >> m;
        seq.assign(m, vector<int>(p));
        freq.assign(m, vector<int>(c + 1, 0));
        tar.assign(m, 0);
        need.assign(m, 0);
        vector<bool> seen(c + 1, false);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                cin >> seq[i][j];
                freq[i][seq[i][j]]++;
                seen[seq[i][j]] = true;
            }
            int b, w;
            cin >> b >> w;
            tar[i] = b;
            need[i] = b + w;
        }
        int miss = 0;
        for (int i = 1; i <= c; i++)
            if (!seen[i]) {
                miss = i;
                break;
            }
        dom.clear();
        for (int i = 1; i <= c; i++)
            if (seen[i] || i == miss) dom.push_back(i);
        mat.assign(m, 0);
        def.assign(m, 0);
        blk.assign(m, 0);
        cnt.assign(c + 1, 0);
        cur.assign(p, 0);
        ans.clear();
        for (int i = 0; i < m; i++)
            for (int x = 1; x <= c; x++)
                def[i] += freq[i][x];
        bool ok = dfs(0);
        if (!ok) {
            cout << "You are cheating!\n";
        } else {
            for (int i = 0; i < p; i++) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
