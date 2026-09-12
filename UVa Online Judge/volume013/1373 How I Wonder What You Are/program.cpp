#include <bits/stdc++.h>
using namespace std;

struct Vec {
    double x, y, z;
};

struct Tel {
    double x, y, z, c;
};

Vec unit(double x, double y, double z) {
    double len = sqrt(x * x + y * y + z * z);
    return {x / len, y / len, z / len};
}

bool see(const Vec &star, const Tel &tel) {
    double val = star.x * tel.x + star.y * tel.y + star.z * tel.z;
    return val > tel.c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n && n) {
        vector<Vec> stars(n);
        double x, y, z, psi;
        for (int i = 0; i < n; i++) {
            cin >> x >> y >> z;
            stars[i] = unit(x, y, z);
        }
        cin >> m;
        vector<Tel> tels(m);
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> z >> psi;
            Vec dir = unit(x, y, z);
            tels[i] = {dir.x, dir.y, dir.z, cos(psi)};
        }
        int ans = 0;
        for (const Vec &star : stars) {
            bool ok = false;
            for (const Tel &tel : tels) {
                if (see(star, tel)) {
                    ok = true;
                    break;
                }
            }
            if (ok) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
