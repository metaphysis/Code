#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> sig, ans, rem, sum;
queue<int> que;
vector<char> inQue;

int id(int x, int y) {
    return x * m + y;
}

void pushEq(int x) {
    if (!inQue[x]) {
        inQue[x] = 1;
        que.push(x);
    }
}

int getWeight(int er, int ec, int vr, int vc) {
    if (er == vr && ec == vc)
        return 4;
    return 1;
}

bool setValue(int x, int value) {
    if (ans[x] != -1)
        return ans[x] == value;
    ans[x] = value;
    int r = x / m, c = x % m;
    for (int i = max(0, r - 1); i <= min(n - 1, r + 1); ++i) {
        for (int j = max(0, c - 1); j <= min(m - 1, c + 1); ++j) {
            int e = id(i, j), w = getWeight(i, j, r, c);
            rem[e] -= w * value;
            sum[e] -= w;
            pushEq(e);
        }
    }
    return true;
}

bool process(int e) {
    int r = e / m, c = e % m;
    vector<pair<int, int> > unknown;
    for (int i = max(0, r - 1); i <= min(n - 1, r + 1); ++i) {
        for (int j = max(0, c - 1); j <= min(m - 1, c + 1); ++j) {
            int x = id(i, j);
            if (ans[x] == -1)
                unknown.push_back(make_pair(x, getWeight(r, c, i, j)));
        }
    }
    if (unknown.empty())
        return rem[e] == 0;
    if (rem[e] < 0 || rem[e] > sum[e])
        return false;
    vector<pair<int, int> > forced;
    for (auto p : unknown) {
        int x = p.first, w = p.second, value = -1;
        if (rem[e] < w)
            value = 0;
        else if (rem[e] > sum[e] - w)
            value = 1;
        if (value != -1)
            forced.push_back(make_pair(x, value));
    }
    for (auto p : forced) {
        if (!setValue(p.first, p.second))
            return false;
    }
    return true;
}

bool solve() {
    while (!que.empty()) {
        int e = que.front();
        que.pop();
        inQue[e] = 0;
        if (!process(e))
            return false;
    }
    for (int x : ans)
        if (x == -1)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int total = n * m;
        sig.assign(total, 0);
        ans.assign(total, -1);
        rem.assign(total, 0);
        sum.assign(total, 0);
        inQue.assign(total, 0);
        while (!que.empty())
            que.pop();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cin >> sig[id(i, j)];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int e = id(i, j);
                rem[e] = sig[e];
                for (int r = max(0, i - 1); r <= min(n - 1, i + 1); ++r) {
                    for (int c = max(0, j - 1); c <= min(m - 1, j + 1); ++c)
                        sum[e] += getWeight(i, j, r, c);
                }
                pushEq(e);
            }
        }
        solve();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << (ans[id(i, j)] == 1 ? 'L' : '-');
            cout << '\n';
        }
    }
    return 0;
}
