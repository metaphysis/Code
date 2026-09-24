#include <bits/stdc++.h>
using namespace std;

int rotateLeft(int val, int cnt) {
    return ((val << cnt) | (val >> (8 - cnt))) & 255;
}

void swapEdge(int val, int bit) {
    int rot = 7 - bit, mask = rotateLeft(val, rot) ^ 127;
    cout << "R " << rot << '\n';
    cout << "X " << mask << '\n';
    cout << "A 1\n";
    cout << "R 1\n";
    cout << "A 254\n";
    cout << "R 7\n";
    cout << "X " << mask << '\n';
    cout << "R " << 8 - rot << '\n';
}

void solve(vector<int> vals) {
    int n = vals.size(), mask = vals[0];
    bool isOk = true;
    for (int i = 0; i < n; i++) isOk = isOk && ((vals[i] ^ mask) == i);
    if (isOk) {
        cout << "X " << mask << '\n';
        cout << "E 0\n";
        return;
    }
    for (int xorVal = 0; xorVal < 256; xorVal++) {
        int addVal = (256 - (vals[0] ^ xorVal)) % 256;
        isOk = true;
        for (int i = 0; i < n; i++) isOk = isOk && (((vals[i] ^ xorVal) + addVal) % 256 == i);
        if (isOk) {
            if (xorVal != 0) cout << "X " << xorVal << '\n';
            if (addVal != 0) cout << "A " << addVal << '\n';
            cout << "E 0\n";
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        if (vals[i] == i) continue;
        int from = vals[i], to = i, diff = from ^ to;
        vector<int> path(1, from), bits;
        for (int bit = 0; bit < 7; bit++) {
            if ((diff & (1 << bit)) != 0) {
                path.push_back(path.back() ^ (1 << bit));
                bits.push_back(bit);
            }
        }
        int len = bits.size();
        for (int j = 0; j < len; j++) swapEdge(path[j], bits[j]);
        for (int j = len - 2; j >= 0; j--) swapEdge(path[j], bits[j]);
        for (int &val : vals) val = val == from ? to : (val == to ? from : val);
    }
    cout << "E 0\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseId = 0;
    while (cin >> n && n != 0) {
        vector<int> vals(n);
        for (int &val : vals) cin >> val;
        cout << "Case " << ++caseId << ":\n";
        solve(vals);
    }
    return 0;
}
