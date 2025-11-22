// Circuit Nets
// UVa ID: 879
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int findSet(int x) {
    if (parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

void unionSet(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);
    if (rootA != rootB) parent[rootB] = rootA;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        cin.ignore(128, '\n'); // 忽略换行符
        
        // 注意：输入可能是多行
        string line;
        while (getline(cin, line) && !line.empty()) {
            stringstream ss(line);
            int a, b;
            while (ss >> a >> b) unionSet(a, b);
        }
        
        unordered_set<int> nets;
        for (int i = 1; i <= n; i++) nets.insert(findSet(i));
        
        cout << nets.size() << endl;
        if (t) cout << endl;
    }
    return 0;
}
