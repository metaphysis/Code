// Interconnect
// UVa ID: 1390
// Verdict: Accepted
// Submission Date: 2026-01-17
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
int n, m;
vector<int> parent, ranks;

int findSet(int x) {
    if (parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

void unionSet(int a, int b) {
    a = findSet(a), b = findSet(b);
    if (a != b) {
        parent[a] = b;
        ranks[b] += ranks[a];
    }
}

// 使用 long long 存储状态掩码（最多 150 位，需要多个 long long）
using StateMask = vector<long long>;

// 获取状态掩码
StateMask getStateMask() {
    vector<int> sizes;
    for (int i = 1; i <= n; i++) if (findSet(i) == i) sizes.push_back(ranks[i]);
    sort(sizes.begin(), sizes.end());
    // 用 vector<long long> 存储，每 12 个分量（60位）用一个 long long
    StateMask mask;
    long long current = 0;
    int bitPos = 0;
    for (int s : sizes) {
        current |= ((long long)s << bitPos);
        bitPos += 5;
        if (bitPos >= 60) {  // 使用 60 位，留出空间
            mask.push_back(current);
            current = 0;
            bitPos = 0;
        }
    }
    if (current != 0 || mask.empty()) mask.push_back(current);
    return mask;
}

// 从掩码解码出分量大小
vector<int> decodeMask(const StateMask& mask) {
    vector<int> sizes;
    for (long long part : mask) {
        long long temp = part;
        while (temp > 0) {
            sizes.push_back(temp & 31);  // 31 = 2^5-1
            temp >>= 5;
        }
    }
    if (sizes.empty()) sizes.push_back(1);
    // 注意：这里需要反转，因为我们是按顺序添加的
    // 但实际上我们需要保持有序，所以先排序
    sort(sizes.begin(), sizes.end());
    return sizes;
}

// 比较两个状态掩码是否相等
bool operator<(const StateMask& a, const StateMask& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}

map<StateMask, double> dp;

double dfs(const StateMask& mask) {
    vector<int> sizes = decodeMask(mask);
    if (sizes.size() == 1) return 0.0;  // 已经连通
    if (dp.count(mask)) return dp[mask];
    int compCount = sizes.size();
    int total = 0;
    for (int sz : sizes) total += sz;
    double totalPairs = total * (total - 1) / 2.0;
    double sameCompPairs = 0.0;
    for (int sz : sizes) sameCompPairs += sz * (sz - 1) / 2.0;
    double pSame = sameCompPairs / totalPairs;
    double r = 0.0;
    for (int i = 0; i < compCount; i++) {
        for (int j = i + 1; j < compCount; j++) {
            double pMerge = (sizes[i] * sizes[j]) / totalPairs;
            // 合并分量i和j
            vector<int> newSizes = sizes;
            newSizes[i] += newSizes[j];
            newSizes.erase(newSizes.begin() + j);
            sort(newSizes.begin(), newSizes.end());
            // 编码新状态
            StateMask newMask;
            long long current = 0;
            int bitPos = 0;
            for (int s : newSizes) {
                current |= ((long long)s << bitPos);
                bitPos += 5;
                if (bitPos >= 60) {
                    newMask.push_back(current);
                    current = 0;
                    bitPos = 0;
                }
            }
            if (current != 0 || newMask.empty()) newMask.push_back(current);
            r += pMerge * dfs(newMask);
        }
    }
    r = (1.0 + r) / (1.0 - pSame);
    dp[mask] = r;
    return r;
}

int main() {
    while (cin >> n >> m) {
        parent.resize(n + 1);
        ranks.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            unionSet(u, v);
        }
        StateMask initialState = getStateMask();
        if (decodeMask(initialState).size() == 1) {
            cout << "0.000000" << endl;
        } else {
            dp.clear();
            double r = dfs(initialState);
            cout << fixed << setprecision(6) << r << endl;
        }
    }
    return 0;
}
