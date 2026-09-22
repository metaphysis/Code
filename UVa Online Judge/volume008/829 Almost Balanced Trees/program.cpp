#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long val;
    int cnt, fa;
};

bool readLine(string &s) {
    while (getline(cin, s))
        if (s.find_first_not_of(" \t\r\n") != string::npos) return true;
    s.clear();
    return false;
}

bool parseTree(const string &s, vector<Node> &tr) {
    istringstream in(s);
    long long val, cnt;
    tr.clear();
    while (true) {
        in >> ws;
        if (in.eof()) break;
        if (!(in >> val >> cnt) || val <= 0 || cnt < 0 || cnt > INT_MAX) return false;
        tr.push_back({val, (int)cnt, -1});
    }
    if (tr.empty()) return false;
    int n = tr.size();
    vector<int> stk, rem(n);
    for (int i = 0; i < n; i++) {
        if (tr[i].cnt >= n) return false;
        rem[i] = tr[i].cnt;
        while (!stk.empty() && !rem[stk.back()]) stk.pop_back();
        if (i) {
            if (stk.empty()) return false;
            tr[i].fa = stk.back();
            rem[stk.back()]--;
        }
        stk.push_back(i);
    }
    while (!stk.empty() && !rem[stk.back()]) stk.pop_back();
    return stk.empty();
}

bool isBalanced(const vector<Node> &tr) {
    int n = tr.size();
    vector<int> mn(n, INT_MAX), mx(n);
    for (int i = n - 1; i >= 0; i--) {
        if (tr[i].cnt && mx[i] - mn[i] > 1) return false;
        if (tr[i].fa != -1) {
            int fa = tr[i].fa, dep = mx[i] + 1;
            mn[fa] = min(mn[fa], dep);
            mx[fa] = max(mx[fa], dep);
        }
    }
    return true;
}

string solve(const string &a, const string &b) {
    vector<Node> ta, tb;
    if (!parseTree(a, ta) || !parseTree(b, tb)) return "-1";
    unordered_set<long long> sa, sb;
    for (const Node &x : ta)
        if (!sa.insert(x.val).second) return "-1";
    for (const Node &x : tb)
        if (!sb.insert(x.val).second) return "-1";
    if (!isBalanced(ta)) return "0";
    int n = ta.size(), m = tb.size();
    if (n == m) {
        vector<int> dif;
        for (int i = 0; i < n; i++) {
            if (ta[i].cnt != tb[i].cnt) return "1 0";
            if (ta[i].val != tb[i].val) dif.push_back(i);
            if (dif.size() > 2) return "1 0";
        }
        if (dif.size() != 2) return "1 0";
        int x = dif[0], y = dif[1];
        if (ta[x].val != tb[y].val || ta[y].val != tb[x].val) return "1 0";
        return "1 " + to_string(min(ta[x].val, ta[y].val)) + " " + to_string(max(ta[x].val, ta[y].val));
    }
    if (m != n - 1) return "1 0";
    int del = -1;
    for (int i = 0; i < n; i++)
        if (!sb.count(ta[i].val)) {
            if (del != -1) return "1 0";
            del = i;
        }
    if (del == -1 || ta[del].cnt) return "1 0";
    for (int i = 0, j = 0; i < n; i++) {
        if (i == del) continue;
        int cnt = ta[i].cnt;
        if (i == ta[del].fa) cnt--;
        if (ta[i].val != tb[j].val || cnt != tb[j].cnt) return "1 0";
        j++;
    }
    return "1 -" + to_string(ta[del].val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < t; i++) {
        string a, b;
        readLine(a);
        readLine(b);
        if (i) cout << '\n';
        cout << solve(a, b) << '\n';
    }
    return 0;
}
