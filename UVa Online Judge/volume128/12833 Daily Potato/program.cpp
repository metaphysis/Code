#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[26], len, link, cnt, ch;
    long long occ;
    Node(int val = 0) : len(val), link(0), cnt(0), ch(-1), occ(0) {
        memset(nxt, 0, sizeof(nxt));
    }
};

class PalTree {
private:
    vector<Node> nod;
    vector<int> pos[26];
    string str;
    int last;

    int getLink(int cur, int idx) {
        while (idx - 1 - nod[cur].len < 0 || str[idx - 1 - nod[cur].len] != str[idx]) cur = nod[cur].link;
        return cur;
    }

    void addChar(int idx) {
        int ch = str[idx] - 'a', cur, nw, st;
        pos[ch].push_back(idx);
        cur = getLink(last, idx);
        if (nod[cur].nxt[ch]) {
            last = nod[cur].nxt[ch];
            nod[last].occ++;
            return;
        }
        nw = nod.size();
        nod.push_back(Node(nod[cur].len + 2));
        nod[cur].nxt[ch] = nw;
        nod[nw].ch = ch;
        if (nod[nw].len == 1) nod[nw].link = 1;
        else {
            cur = getLink(nod[cur].link, idx);
            nod[nw].link = nod[cur].nxt[ch];
        }
        st = idx - nod[nw].len + 1;
        nod[nw].cnt = pos[ch].end() - lower_bound(pos[ch].begin(), pos[ch].end(), st);
        last = nw;
        nod[last].occ++;
    }

public:
    PalTree(const string &s) : str(s), last(1) {
        nod.push_back(Node(-1));
        nod.push_back(Node(0));
        nod[0].link = 0;
        nod[1].link = 0;
    }

    void build() {
        int n = str.size();
        for (int i = 0; i < n; i++) addChar(i);
    }

    void countOcc() {
        vector<int> ord;
        int m = nod.size();
        for (int i = 0; i < m; i++) ord.push_back(i);
        sort(ord.begin(), ord.end(), [this](int a, int b) { return nod[a].len > nod[b].len; });
        for (int id : ord)
            if (id >= 2) nod[nod[id].link].occ += nod[id].occ;
    }

    void fillAns(vector<vector<long long> > &ans) {
        int m = nod.size();
        for (int i = 2; i < m; i++) ans[nod[i].ch][nod[i].cnt] += nod[i].occ;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, q;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        string s, qs;
        cin >> n >> s >> q >> qs;
        vector<int> x(q);
        for (int i = 0; i < q; i++) cin >> x[i];
        n = s.size();
        PalTree tree(s);
        tree.build();
        tree.countOcc();
        vector<vector<long long> > ans(26, vector<long long>(n + 1, 0));
        tree.fillAns(ans);
        cout << "Case " << tc << ":\n";
        for (int i = 0; i < q; i++) {
            int ch = qs[i] - 'a';
            if (x[i] < 1 || x[i] > n) cout << 0 << '\n';
            else cout << ans[ch][x[i]] << '\n';
        }
    }
    return 0;
}
