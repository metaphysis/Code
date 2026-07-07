// Lattice Practices
// UVa ID: 687
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int original[10], reversed[10], H[5], V[5];
bool symmetry[10], used[10];

int getReverse(int x) {
    int y = 0;
    for (int i = 0; i < 5; ++i)
        if (x & (1 << i)) y |= (1 << (4 - i));
    return y;
}

int toMask(const string &s) {
    int x = 0;
    for (int i = 0; i < 5; ++i)
        if (s[i] == '1') x |= (1 << i);
    return x;
}

bool checkRow(int r) {
    for (int c = 4; c >= 0; c--) {
        if (V[c] == -1) continue;
        int hb = (H[r] >> c) & 1;
        int vb = (V[c] >> r) & 1;
        if (hb + vb != 1) return false;
    }
    return true;
}

bool checkCln(int c) {
    for (int r = 4; r >= 0; r--) {
        if (H[r] == -1) continue;
        int hb = (H[r] >> c) & 1;
        int vb = (V[c] >> r) & 1;
        if (hb + vb != 1) return false;
    }
    return true;
}

pair<int,int> transform(int op, int r, int c) {
    switch(op) {
        case 0: return {r, c};
        case 1: return {c, 4 - r};
        case 2: return {4 - r, 4 - c};
        case 3: return {4 - c, r};
        case 4: return {r, 4 - c};
        case 5: return {4 - r, c};
        case 6: return {c, r};
        case 7: return {4 - c, 4 - r};
    }
    return {r, c};
}

string toString(int bits) {
    string s;
    for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c)
            s += (bits & (1 << (r * 5 + c))) ? '1' : '0';
    return s;
}

set<string> all;

void normalize() {
    int bits = 0;
    for (int i = 0; i < 5; i++) bits |= H[i] << (5 * i);
    string best = toString(bits);
    for (int op = 1; op < 8; ++op) {
        int nb = 0;
        for (int r = 0; r < 5; ++r)
            for (int c = 0; c < 5; ++c)
                if (bits & (1 << (r * 5 + c))) {
                    auto p = transform(op, r, c);
                    nb |= (1 << (p.first * 5 + p.second));
                }
        string s = toString(nb);
        if (s < best) best = s;
    }
    all.insert(best);
}

void dfs(int step) {
    if (step == 10) {
        normalize();
        return;
    }
    if (step % 2 == 0) {
        int r = step / 2;
        if (H[r] != -1) {
            dfs(step + 1);
            return;
        }
        for (int id = 0; id < 10; ++id) {
            if (used[id]) continue;
            used[id] = true;
            H[r] = original[id];
            if (checkRow(r))
                dfs(step + 1);
            H[r] = -1;
            used[id] = false;
            if (!symmetry[id]) {
                used[id] = true;
                H[r] = reversed[id];
                if (checkRow(r))
                    dfs(step + 1);
                H[r] = -1;
                used[id] = false;
            }
        }
    } else {
        int c = step / 2;
        if (V[c] != -1) {
            dfs(step + 1);
            return;
        }
        for (int id = 0; id < 10; ++id) {
            if (used[id]) continue;
            used[id] = true;
            V[c] = original[id];
            if (checkCln(c))
                dfs(step + 1);
            V[c] = -1;
            used[id] = false;
            if (!symmetry[id]) {
                used[id] = true;
                V[c] = reversed[id];
                if (checkCln(c))
                    dfs(step + 1);
                V[c] = -1;
                used[id] = false;
            }
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string token;
    while (cin >> token) {
        if (token == "END") break;
        vector<int> boards(10);
        boards[0] = toMask(token);
        for (int i = 1; i < 10; ++i) {
            cin >> token;
            boards[i] = toMask(token);
        }
        for (int i = 0; i < 10; ++i) {
            original[i] = boards[i];
            reversed[i] = getReverse(original[i]);
            symmetry[i] = (original[i] == reversed[i]);
        }
        all.clear();
        memset(used, 0, sizeof(used));
        for (int i = 0; i < 5; ++i) H[i] = V[i] = -1;
        dfs(0);
        cout << all.size() / 2 << '\n';
    }
    return 0;
}
