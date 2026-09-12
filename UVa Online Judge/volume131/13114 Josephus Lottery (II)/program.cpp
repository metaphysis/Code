#include <bits/stdc++.h>
using namespace std;

int getWin(int k) {
    vector<int> a(100);
    int cur = 0, dir = 1;
    for (int i = 0; i < 100; i++) a[i] = i + 1;
    while (a.size() > 1) {
        int n = (int)a.size(), step = (k - 1) % n, pos;
        if (dir == 1) pos = (cur + step) % n;
        else pos = (cur - step + n) % n;
        a.erase(a.begin() + pos);
        n--;
        if (dir == 1) cur = pos % n;
        else cur = (pos - 1 + n) % n;
        dir = -dir;
    }
    return a[0];
}

vector<int> getAns() {
    vector<int> ans(101, 0);
    for (int k = 1; k <= 1000; k++) {
        int win = getWin(k);
        if (ans[win] == 0) ans[win] = k;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> ans = getAns();
    int m;
    while (cin >> m) {
        if (m == 0) break;
        cout << ans[m] << '\n';
    }
    return 0;
}
