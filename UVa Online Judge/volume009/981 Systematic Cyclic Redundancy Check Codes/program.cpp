#include <bits/stdc++.h>
using namespace std;

bool checkCrc(string e, const string &g) {
    int n = (int)e.size(), m = (int)g.size();
    if (n < m)
        return false;
    for (int i = 0; i + m <= n; ++i)
        if (e[i] == '1')
            for (int j = 0; j < m; ++j)
                e[i + j] = e[i + j] == g[j] ? '0' : '1';
    for (int i = n - m + 1; i < n; ++i)
        if (e[i] == '1')
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    string e, g;
    while (cin >> k >> e >> g) {
        if (checkCrc(e, g)) cout << e.substr(0, k) << '\n';
        else cout << "ERROR\n";
    }
    return 0;
}
