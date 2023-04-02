// Ignoring Digits
// UVa ID: 10993
// Verdict: Accepted
// Submission Date: 2023-04-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct block { int pre, idx, digit, mod; } g[1000010];

int visited[100010];

void dfs(int d) {
    if (g[d].pre) dfs(g[g[d].pre].idx);
    cout << g[d].digit;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string F;
    int N;
    while (cin >> F >> N) {
        if (N == 0) break;
        int available = 0;
        for (int i = 0; i < F.length(); i++) available |= 1 << (F[i] - '0');
        for (int i = 0; i < N; i++) visited[i] = 0;
        int cnt = 1;
        for (int i = 1; i < 10; i++) {
            if (available & (1 << i)) {
                g[cnt] = block{0, cnt, i, i % N};
                cnt++;
                visited[i % N] = 1;
            }
        }
        int head = 1, rear = cnt, flag = 0;
        while (head < rear && !flag) {
            while (head < rear) {
                block b = g[head++];
                if (!b.mod) {
                    flag = b.idx;
                    break;
                }
                for (int i = 0; i < 10; i++)
                    if (available & (1 << i)) {
                        int mod = (b.mod * 10 + i) % N;
                        if (visited[mod]) continue;
                        visited[mod] = 1;
                        g[cnt] = block{b.idx, cnt, i, mod};
                        cnt++;
                    }
            }
            head = rear, rear = cnt;
        }
        if (!flag) cout << "impossible";
        else dfs(flag);
        cout << '\n';
    }
    return 0;
}
