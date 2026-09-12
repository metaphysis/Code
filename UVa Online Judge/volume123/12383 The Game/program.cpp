#include <bits/stdc++.h>
using namespace std;

struct Node {
    long double val;
    int cnt;
};

long double solveFirst(int n, int m) {
    deque<long double> que;
    long double sum = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int cnt = min(m, i - 1);
        ans = ((i <= m ? 1 : 0) + cnt - sum) / m;
        que.push_back(ans);
        sum += ans;
        if ((int)que.size() > m) {
            sum -= que.front();
            que.pop_front();
        }
    }
    return ans;
}

long double solveSecond(int n, int m) {
    deque<Node> que;
    long double sum = 0, ans = 0;
    int len = 1;
    que.push_back({0, 1});
    for (int i = 1; i <= n; i++) {
        int cnt = 1;
        ans = (m - sum) / m;
        while (!que.empty() && que.front().val >= ans) {
            cnt += que.front().cnt;
            sum -= que.front().val * que.front().cnt;
            len -= que.front().cnt;
            que.pop_front();
        }
        que.push_front({ans, cnt});
        sum += ans * cnt;
        len += cnt;
        while (len > m) {
            int del = min(len - m, que.back().cnt);
            sum -= que.back().val * del;
            que.back().cnt -= del;
            len -= del;
            if (que.back().cnt == 0) que.pop_back();
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    cout << fixed << setprecision(4);
    while (t--) {
        int n, m;
        cin >> n >> m;
        long double first = solveFirst(n, m), second = solveSecond(n, m);
        if (fabsl(first) < 0.0000000001L) first = 0;
        if (fabsl(second) < 0.0000000001L) second = 0;
        cout << (double)first << ' ' << (double)second << '\n';
    }
    return 0;
}
