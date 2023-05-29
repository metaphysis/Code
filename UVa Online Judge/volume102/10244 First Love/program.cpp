// First Love
// UVa ID: 10244
// Verdict: Accepted
// Submission Date: 2023-05-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
set<string> cache;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string bit;
    int n;
    while (cin >> bit >> n) {
        sort(bit.begin(), bit.end());
        int k = bit.length();
        long long t = (long long)pow(k, n) + n - 1;
        cout << t << '\n';
        if (t > 10000) cout << "TOO LONG TO PRINT.\n";
        else {
            if (n == 1) { cout << bit << '\n'; continue; }
            cache.clear();
            stack<string> path;
            vector<char> circuit;
            string u = string(n - 1, bit.front());
            path.push(u);
            while (!path.empty()) {
                int v = 0;
                for (v = 0; v < k; v++)
                    if (!cache.count(u + bit[v]))
                        break;
                if (v < k) {
                    path.push(u);
                    cache.insert(u + bit[v]);
                    u = u.substr(1) + bit[v];
                } else {
                    circuit.push_back(u.back());
                    u = path.top();
                    path.pop();
                }
            }
            string r;
            for (int i = circuit.size() - 2; i >= 0; i--) r += circuit[i];
            // 注意，当给定的字符串长度为 1，但 N 大于 1 时，circuit 的大小为 2，
            // 此时不能使用以下语句来获取结果：
            // for (int i = circuit.size() - 2, j = 0; j < n - 1; i--, j++) r += circuit[i];
            // 这样会导致错误，而应使用以下的语句：
            for (int i = 0; i < n - 1; i++) r += r[i];
            cout << r << '\n';
        }
    }
    return 0;
}
