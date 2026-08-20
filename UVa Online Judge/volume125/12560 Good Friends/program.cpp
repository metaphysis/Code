#include <bits/stdc++.h>
using namespace std;

const int maxM = 10000;
bitset<maxM> act[30];
vector<unsigned int> candAns;
int n, m, lim;

void dfs(unsigned int mask, const vector<int>& cand, const bitset<maxM>& now) {
    bitset<maxM> all = now;
    for (int x : cand) all &= act[x];
    if ((int)all.count() >= lim) {
        unsigned int full = mask;
        for (int x : cand) full |= (1u << x);
        if (__builtin_popcount(full) >= 2) candAns.push_back(full);
        return;
    }
    for (int i = 0; i < (int)cand.size(); i++) {
        int x = cand[i];
        bitset<maxM> nxt = now & act[x];
        if ((int)nxt.count() < lim) continue;
        vector<int> sub;
        for (int j = i + 1; j < (int)cand.size(); j++) {
            int y = cand[j];
            if ((int)(nxt & act[y]).count() >= lim) sub.push_back(y);
        }
        dfs(mask | (1u << x), sub, nxt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> m;
        lim = (m + 4) / 5;
        for (int i = 0; i < n; i++) act[i].reset();
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            while (k--) {
                int x;
                cin >> x;
                act[x - 1].set(i);
            }
        }
        vector<int> cand;
        candAns.clear();
        for (int i = 0; i < n; i++) {
            if ((int)act[i].count() >= lim) cand.push_back(i);
        }
        bitset<maxM> all;
        for (int i = 0; i < m; i++) all.set(i);
        dfs(0, cand, all);
        vector<unsigned int> ans;
        for (int i = 0; i < (int)candAns.size(); i++) {
            bool ok = true;
            for (int j = 0; j < (int)candAns.size(); j++) {
                if (i != j && candAns[i] != candAns[j] && (candAns[i] | candAns[j]) == candAns[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans.push_back(candAns[i]);
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        vector<vector<int> > out;
        for (unsigned int mask : ans) {
            vector<int> group;
            for (int i = 0; i < n; i++) {
                if (mask & (1u << i)) group.push_back(i + 1);
            }
            out.push_back(group);
        }
        sort(out.begin(), out.end());
        cout << "Case " << tc << ": " << out.size() << '\n';
        for (const vector<int>& group : out) {
            for (int i = 0; i < (int)group.size(); i++) {
                if (i) cout << ' ';
                cout << group[i];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
