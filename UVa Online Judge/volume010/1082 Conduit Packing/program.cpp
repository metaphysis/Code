#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
double rad[5], que[6], f[6];
bool used[5];

bool check(double p1, double p2, double p3) {
    if (p1 > p2) swap(p1, p2);
    if (p1 > p3) swap(p1, p3);
    if (p2 > p3) swap(p2, p3);
    if (p1 <= 0) return false;
    if (p1 + p2 <= p3) return false;
    return true;
}

bool dfs(int dep, double key) {
    int i, j;
    double tmp, p1, p2, p3;
    if (dep > 4) {
        if (que[1] < que[2] || que[1] < que[3] || que[1] < que[4]) return false;
        for (i = 1; i <= 5; i++) f[i] = 0;
        que[5] = que[1];
        for (i = 2; i <= 5; i++) {
            for (j = 1; j < i; j++) {
                if (j == 1 && i == 5) continue;
                p1 = key - que[i];
                p2 = key - que[j];
                p3 = que[i] + que[j];
                if (check(p1, p2, p3) == false) return false;
                tmp = (p1 * p1 + p2 * p2 - p3 * p3) / (2 * p1 * p2);
                tmp = max(-1.0, min(1.0, tmp));
                tmp = acos(tmp);
                if (tmp + f[j] > f[i]) f[i] = tmp + f[j];
            }
        }
        if (f[5] > 2 * pi) return false;
        return true;
    }
    for (i = 1; i <= 4; i++) {
        if (used[i]) continue;
        used[i] = true;
        que[dep] = rad[i];
        if (dfs(dep + 1, key)) return true;
        used[i] = false;
    }
    return false;
}

bool canFit(double key) {
    memset(used, false, sizeof(used));
    return dfs(1, key);
}

int main() {
    int caseNo = 0, i;
    double low, high, mid;
    while (cin >> rad[1] && rad[1] != 0) {
        for (i = 2; i <= 4; i++) cin >> rad[i];
        low = 0;
        high = 100000;
        while (high - low > 1e-8) {
            mid = (low + high) / 2;
            if (canFit(mid)) high = mid;
            else low = mid;
        }
        cout << "Case " << ++caseNo << ": " << (long long)(high + 0.5) << '\n';
    }
    return 0;
}
