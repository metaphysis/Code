// Leonardo's Notebook
// UVa ID: 12103
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool canBeSquare(const string& perm) {
    int n = perm.size();
    vector<bool> visited(n, false);
    int count[27] = {0}; // 统计各长度循环出现的次数

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int len = 0;
            int cur = i;
            while (!visited[cur]) {
                visited[cur] = true;
                cur = perm[cur] - 'A';
                len++;
            }
            count[len]++;
        }
    }

    // 检查偶数长度循环是否成对出现
    for (int len = 2; len <= n; len += 2) {
        if (count[len] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string perm;
        cin >> perm;
        if (canBeSquare(perm)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
