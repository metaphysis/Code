#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool check(array<array<ll, 3>, 3>& d, array<ll, 3>& t) {
    ll ax = d[0][0] - d[2][0], ay = d[0][1] - d[2][1];
    ll bx = d[1][0] - d[2][0], by = d[1][1] - d[2][1];
    ll tx = t[0] - d[2][0], ty = t[1] - d[2][1];
    ll det = ax * by - ay * bx;
    if (det != 0) {
        ll nx = tx * by - ty * bx;
        ll ny = ax * ty - ay * tx;
        ll nz = det - nx - ny;
        return nx * det > 0 && ny * det > 0 && nz * det > 0;
    }
    int id = 1;
    if (d[1] == d[0]) id = 2;
    if (d[id] == d[0]) return t == d[0];
    ll dx = d[id][0] - d[0][0], dy = d[id][1] - d[0][1];
    ll ux = t[0] - d[0][0], uy = t[1] - d[0][1];
    if (dx * uy != dy * ux) return false;
    int p = dx != 0 ? 0 : 1;
    ll mn = min(d[0][p], min(d[1][p], d[2][p]));
    ll mx = max(d[0][p], max(d[1][p], d[2][p]));
    return mn < t[p] && t[p] < mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    array<array<ll, 3>, 3> d;
    array<ll, 3> t;
    while (cin >> d[0][0] >> d[0][1] >> d[0][2]) {
        if (d[0][0] == 0 && d[0][1] == 0 && d[0][2] == 0) break;
        for (int i = 1; i < 3; i++)
            cin >> d[i][0] >> d[i][1] >> d[i][2];
        cin >> t[0] >> t[1] >> t[2];
        cout << (check(d, t) ? "YES" : "NO") << '\n';
    }
    return 0;
}
