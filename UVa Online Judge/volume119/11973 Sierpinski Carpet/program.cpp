#include <bits/stdc++.h>
using namespace std;

const int scale = 1000000;

int parseValue(const string &s) {
    int val = 0, frac = 0, cnt = 0;
    bool dot = false;
    for (char ch : s) {
        if (ch == '.') {
            dot = true;
        } else if (!dot) {
            val = val * 10 + ch - '0';
        } else {
            frac = frac * 10 + ch - '0';
            cnt++;
        }
    }
    while (cnt < 6) {
        frac *= 10;
        cnt++;
    }
    return val * scale + frac;
}

int solve(int x, int y) {
    unordered_set<long long> seen;
    int step = 1;
    while (true) {
        long long key = (static_cast<long long>(x) << 20) | y;
        if (seen.count(key)) return -1;
        seen.insert(key);
        int tx = x * 3, ty = y * 3;
        int dx = tx / scale, dy = ty / scale;
        if (dx == 1 && dy == 1) return step - 1;
        x = tx % scale;
        y = ty % scale;
        step++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        string sx, sy;
        cin >> sx >> sy;
        int x = parseValue(sx), y = parseValue(sy);
        cout << "Case " << i << ": " << solve(x, y) << '\n';
    }
    return 0;
}
