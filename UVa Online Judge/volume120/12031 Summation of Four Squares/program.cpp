#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll answer[10];
int primes[11] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

bool dfs(int depth, ll now, ll multiply) {
    if (!now) {
        for (int i = depth; i < 4; i++) answer[i] = 0;
        return true;
    }
    if (depth >= 4) return false;
    for (int i = 1; i <= 10; i++) {
        ll sq = 1LL * primes[i] * primes[i];
        while (now % sq == 0) {
            now /= sq;
            multiply *= primes[i];
        }
    }
    ll t = sqrt((long double)now);
    while ((t + 1) * (t + 1) <= now) t++;
    while (t * t > now) t--;
    if (depth == 3) {
        if (t * t != now) return false;
        answer[depth] = t * multiply;
        return true;
    }
    int limit;
    if (depth == 0) limit = 1000;
    else limit = 2;
    for (int i = 0; i <= limit && t >= 0; i++) {
        answer[depth] = t * multiply;
        if (dfs(depth + 1, now - t * t, multiply)) return true;
        t--;
    }
    return false;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    ll n;
    while (T--) {
        cin >> n;
        if (dfs(0, n, 1)) cout << answer[0] << ' ' << answer[1] << ' ' << answer[2] << ' ' << answer[3] << '\n';
        else cout << "Impossible.\n";
    }
    return 0;
}
