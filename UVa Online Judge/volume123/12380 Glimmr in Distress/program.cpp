#include <bits/stdc++.h>
using namespace std;

string str;
int idx, maxDep;

int parseTree(int dep) {
    if (idx >= (int)str.size()) return -1;
    char ch = str[idx++];
    if (ch == '0' || ch == '1') {
        maxDep = max(maxDep, dep);
        return ch - '0';
    }
    if (ch != '2') return -1;
    int a[4];
    for (int i = 0; i < 4; i++) {
        a[i] = parseTree(dep + 1);
        if (a[i] == -1) return -1;
    }
    if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3] && (a[0] == 0 || a[0] == 1)) return -1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> str;
        idx = 0;
        maxDep = 0;
        int type = parseTree(0);
        bool ok = type != -1 && idx == (int)str.size();
        if (ok) cout << "2^" << maxDep << "*2^" << maxDep << '\n';
        else cout << "Not Possible\n";
    }
    return 0;
}
