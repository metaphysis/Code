#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, move[128], visited[128];
    while (cin >> n, n) {
        memset(visited, 0, sizeof visited);
        long long lcm = 1;
        for (int i = 1; i <= n; i++) cin >> move[i];
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            int now = i, cnt = 0;
            while (!visited[now]) {
                visited[now] = 1;
                now = move[now];
                cnt++;
            }
            lcm = lcm / __gcd(lcm, 1LL * cnt) * cnt;
        }
        cout << lcm << '\n';
    }
    return 0;
}
