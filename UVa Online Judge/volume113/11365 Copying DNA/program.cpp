#include <bits/stdc++.h>
using namespace std;

int solveCase(const string &s, const string &t) {
    int n = t.size(), total = 1 << n, full = total - 1, count = n * (n + 1) / 2;
    vector<int> leftPos(count), rightPos(count), segMask(count), base(count, 0);
    vector<vector<int>> need(count);
    int id = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            string x = t.substr(l, r - l + 1), y = x;
            reverse(y.begin(), y.end());
            leftPos[id] = l;
            rightPos[id] = r;
            segMask[id] = ((1 << (r - l + 1)) - 1) << l;
            if (s.find(x) != string::npos || s.find(y) != string::npos)
                base[id] = 1;
            id++;
        }
    }
    for (int i = 0; i < count; i++) {
        int len = rightPos[i] - leftPos[i] + 1;
        string x = t.substr(leftPos[i], len), y = x;
        reverse(y.begin(), y.end());
        id = 0;
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                if (r - l + 1 == len) {
                    string z = t.substr(l, len);
                    string w = z;
                    reverse(w.begin(), w.end());
                    if (z == x || z == y || w == x || w == y)
                        need[i].push_back(segMask[id]);
                }
                id++;
            }
        }
    }
    vector<int> dist(total, -1), queueState;
    queueState.push_back(0);
    dist[0] = 0;
    for (int head = 0; head < (int)queueState.size(); head++) {
        int mask = queueState[head];
        if (mask == full)
            return dist[mask];
        for (int i = 0; i < count; i++) {
            if (mask & segMask[i])
                continue;
            bool canCopy = base[i];
            if (!canCopy) {
                for (int sourceMask : need[i]) {
                    if ((mask & sourceMask) == sourceMask) {
                        canCopy = true;
                        break;
                    }
                }
            }
            if (!canCopy)
                continue;
            int nextMask = mask | segMask[i];
            if (dist[nextMask] == -1) {
                dist[nextMask] = dist[mask] + 1;
                queueState.push_back(nextMask);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        string s, t;
        cin >> s >> t;
        int answer = solveCase(s, t);
        if (answer == -1)
            cout << "impossible\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
