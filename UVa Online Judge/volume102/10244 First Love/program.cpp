// First Love
// UVa ID: 10244
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        long long k = bit.length();
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
                for (v = 0; v < bit.length(); v++)
                    if (!cache.count(u + bit[v]))
                        break;
                if (v < bit.length()) {
                    path.push(u);
                    cache.insert(u + bit[v]);
                    u = u.substr(1) + bit[v];
                } else {
                    circuit.push_back(u.back());
                    u = path.top();
                    path.pop();
                }
            }
            for (int i = circuit.size() - 2; i >= 0; i--) cout << circuit[i];
            for (int i = circuit.size() - 2, j = 1; j < n; i--, j++) cout << circuit[i];
            cout << '\n';
        }
    }
    return 0;
}
