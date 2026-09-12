#include <bits/stdc++.h>
using namespace std;

map<int, string> nameMap;

string dfs(int l, int r, vector<int>& val, map<int, int>& pos, char key) {
    if (l == r) {
        if (l == 0) return string(1, key);
        int x = val[l];
        return string(1, nameMap[x][pos[x]++]);
    }
    int mid = (l + r) / 2, cnt = 2;
    string ans(r - l + 1, 'z');
    map<int, int> oldPos = pos;
    while (cnt--) {
        pos = oldPos;
        int l1 = l, r1 = mid, l2 = mid + 1, r2 = r;
        if (cnt) {
            swap(l1, l2);
            swap(r1, r2);
        }
        string s1 = dfs(l1, r1, val, pos, key), s2 = dfs(l2, r2, val, pos, key);
        if (s1 > s2) swap(s1, s2);
        ans = min(ans, s1 + s2);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    while (testNum--) {
        int n, tot, key;
        char ch;
        cin >> n >> ch;
        tot = 1 << n;
        key = isupper(ch) ? ch - 'A' : ch - 'a' + 26;
        vector<pair<int, int>> team;
        nameMap.clear();
        for (int i = 0; i < tot; i++) {
            int score;
            char cur;
            cin >> score;
            cur = i < 26 ? char('A' + i) : char('a' + i - 26);
            team.push_back({score, i});
            if (i != key) nameMap[score] += cur;
        }
        sort(team.begin(), team.end());
        for (int i = tot - 1; i > 0; i--)
            if (team[i].second == key) swap(team[i - 1], team[i]);
        vector<int> val;
        for (int i = 0; i < tot; i++) val.push_back(team[i].first);
        map<int, int> pos;
        cout << dfs(0, tot - 1, val, pos, ch) << '\n';
    }
    return 0;
}
