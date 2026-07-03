// The Rotating Disk
// UVa ID: 605
// Verdict: Accepted
// Submission Date: 2026-07-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using Vi = vector<int>;

const int NONE = -1;
const string tip = "It is not possible to rearrange these disks in natural order.";

void flip(Vi& v, int i) {
    int n = v.size();
    swap(v[i], v[(i + 3) % n]);
    swap(v[(i + 1) % n], v[(i + 2) % n]);
}

void execute(Vi& v, int l) {
    int n = v.size(), r = (l + 3) % n;
    for (int i = 0; i < n; ++i) {
        if (i == l) cout << '*';
        cout << v[i];
        if (i == r) cout << '*';
        cout << " \n"[i + 1 == n];
    }
}

bool validate(Vi& v) {
    int cnt = 0, n = v.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (v[i] > v[j]) ++cnt;
    if (cnt & 1) {
        if (n & 1) return false;
        v.push_back(v[0]);
        v.erase(v.begin());
    }
    return true;
}

void fix(Vi& v) {
    int n = v.size();
    for (int d = n; d > 6; --d) {
        int t = d - 1;
        while (v[t] != d) {
            int s = find(v.begin(), v.end(), d) - v.begin();
            if ((t - s) % 3 == 0 || s <= 1) {
                flip(v, s);
                execute(v, s);
            } else {
                flip(v, s - 2);
                execute(v, s - 2);
            }
        }
    }
}

void trick(Vi& v) {
    int idx = find(v.begin(), v.end(), 1) - v.begin();
    int good = 1;
    for (int i = 0; i < 4; i++)
        if (v[(i + idx) % 4] != i + 1) {
            good = 0;
            break;
        }
    if (!good) cout << tip << '\n';
}

void solve(Vi& v) {
    if (v.size() <= 4) trick(v);
    else {
        fix(v);
        Vi goal = v;
        sort(goal.begin(), goal.end());
        map<Vi, int> seen;
        queue<Vi> q;
        seen[goal] = NONE;
        q.push(goal);
        while (!q.empty()) {
            if (seen.count(v)) break;
            auto vv = q.front(); q.pop();
            for (int i = 0; i <= 2; ++i) {
                Vi nxt = vv;
                flip(nxt, i);
                if (!seen.count(nxt)) {
                    seen[nxt] = i;
                    q.push(nxt);
                }
            }
        }
        while (seen[v] != NONE) {
            int p = seen[v];
            flip(v, p);
            execute(v, p);
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cases = 0;
    while (getline(cin, line)) {
        if (cases++) cout << '\n';
        istringstream iss(line);
        Vi v;
        int n;
        while (iss >> n) {
            if (v.size()) cout << ' ';
            v.push_back(n);
            cout << n;
        }
        cout << '\n';
        if (!validate(v)) {
            cout << tip << '\n';
            continue;
        }
        assert(v.size() >= 4);
        solve(v);
    }
    return 0;
}
