#include <bits/stdc++.h>
using namespace std;

long long getCoef(const string &str, char key) {
    int pos, idx, end;
    long long val;
    pos = str.find(key);
    idx = pos - 1;
    end = idx;
    while (idx >= 0 && isdigit(static_cast<unsigned char>(str[idx])))
        idx--;
    val = 1;
    if (end >= idx + 1)
        val = stoll(str.substr(idx + 1, end - idx));
    if (idx >= 0 && str[idx] == '-')
        val = -val;
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cx, cy, n;
    while (cin >> cx >> cy >> n) {
        if (n == 0)
            break;
        long long pos, neg, dx, dy, aa, bb, cr;
        string eq;
        pos = 0;
        neg = 0;
        for (int i = 0; i < n; i++) {
            cin >> dx >> dy >> eq;
            aa = getCoef(eq, 'x');
            bb = getCoef(eq, 'y');
            dx -= cx;
            dy -= cy;
            cr = dx * bb - dy * aa;
            if (cr > 0)
                pos++;
            else
                neg++;
        }
        cout << pos * neg << '\n';
    }
    return 0;
}
