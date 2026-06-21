// Antonyms
// UVa ID: 11870
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> parent, diff;   // diff[x] 表示 x 与 parent[x] 的关系（0 同义，1 反义）
    unordered_map<string, int> id;

    // 获取单词的编号，若不存在则新建节点
    int getID(const string &s) {
        auto it = id.find(s);
        if (it != id.end()) return it->second;
        int newId = parent.size();
        id[s] = newId;
        parent.push_back(newId);
        diff.push_back(0);      // 自己与自己同义
        return newId;
    }

    // 查找根节点，同时路径压缩并更新 diff
    int findSet(int x) {
        if (parent[x] != x) {
            int orig = parent[x];
            parent[x] = findSet(parent[x]);
            diff[x] ^= diff[orig];   // 更新 x 到新根的关系
        }
        return parent[x];
    }

    // 合并 x 和 y，关系为 r（0 同义，1 反义），返回是否矛盾
    bool unite(int x, int y, int r) {
        int rx = findSet(x), ry = findSet(y);
        if (rx == ry)
            return ((diff[x] ^ diff[y]) == r);   // 检查已有关系是否一致
        // 将 rx 挂在 ry 下，计算 rx 到 ry 的关系
        parent[rx] = ry;
        diff[rx] = diff[x] ^ diff[y] ^ r;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, M;
        cin >> N >> M;
        UnionFind uf;
        bool ok = true;
        string a, b;

        // 读入同义词对
        for (int i = 0; i < N; ++i) {
            cin >> a >> b;
            if (!ok) continue;
            int idA = uf.getID(a), idB = uf.getID(b);
            if (!uf.unite(idA, idB, 0)) ok = false;
        }

        // 读入反义词对
        for (int i = 0; i < M; ++i) {
            cin >> a >> b;
            if (!ok) continue;
            int idA = uf.getID(a), idB = uf.getID(b);
            if (!uf.unite(idA, idB, 1)) ok = false;
        }

        cout << "Case " << caseNo << ": " << (ok ? "YES" : "NO") << "\n";
    }

    return 0;
}
