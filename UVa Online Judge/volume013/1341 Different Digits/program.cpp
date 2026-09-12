#include <bits/stdc++.h>
using namespace std;

bool better(const string& a, const string& b) {
    if (b.empty()) return true;
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

string build(int rem, const vector<int>& pre, const vector<char>& pd) {
    string ans;
    for (int x = rem; x != -1; x = pre[x]) ans.push_back(pd[x]);
    reverse(ans.begin(), ans.end());
    return ans;
}

string findMin(int n, const vector<int>& ds) {
    vector<int> pre(n, -2);
    vector<char> pd(n);
    queue<int> que;
    for (int d : ds) {
        if (d == 0) continue;
        int rem = d % n;
        if (pre[rem] != -2) continue;
        pre[rem] = -1;
        pd[rem] = char('0' + d);
        if (rem == 0) return build(rem, pre, pd);
        que.push(rem);
    }
    while (!que.empty()) {
        int rem = que.front();
        que.pop();
        for (int d : ds) {
            int next = (rem * 10 + d) % n;
            if (pre[next] != -2) continue;
            pre[next] = rem;
            pd[next] = char('0' + d);
            if (next == 0) return build(next, pre, pd);
            que.push(next);
        }
    }
    return "";
}

int solve() {
    int n;
    while (cin >> n && n) {
        string ans;
        for (int d = 1; d <= 9; d++) {
            vector<int> ds(1, d);
            string cur = findMin(n, ds);
            if (!cur.empty() && better(cur, ans)) ans = cur;
        }
        if (ans.empty()) {
            for (int i = 0; i <= 9; i++) {
                for (int j = i + 1; j <= 9; j++) {
                    vector<int> ds;
                    ds.push_back(i);
                    ds.push_back(j);
                    string cur = findMin(n, ds);
                    if (!cur.empty() && better(cur, ans)) ans = cur;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
