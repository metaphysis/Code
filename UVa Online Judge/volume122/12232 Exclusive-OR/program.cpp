// Exclusive-OR
// UVa ID: 12232
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
int parent[MAXN];      // 并查集父节点
int diff[MAXN];        // diff[x] = X[x] ^ X[parent[x]]
int rootValue[MAXN];   // rootValue[r] = X[r] 的值，-1 表示未知
int n, q;              // n 个变量，q 条询问/事实
int caseId;            // 测试用例编号

// 查找根节点，同时更新 diff 值
int find(int x) {
    if (parent[x] != x) {
        int root = find(parent[x]);
        diff[x] ^= diff[parent[x]];
        parent[x] = root;
    }
    return parent[x];
}

// 合并两个集合，已知 x ^ y = val
bool merge(int x, int y, int val) {
    int rx = find(x), ry = find(y);
    if (rx == ry) {
        // 如果已经在同一集合，检查一致性
        return (diff[x] ^ diff[y]) == val;
    }
    // 总是将小根作为父亲
    if (rx > ry) {
        swap(rx, ry);
        swap(x, y);
    }
    parent[ry] = rx;
    diff[ry] = diff[x] ^ diff[y] ^ val;
    
    // 传播已知值
    if (rootValue[rx] != -1 && rootValue[ry] != -1) {
        return rootValue[ry] == (rootValue[rx] ^ diff[ry]);
    }
    if (rootValue[ry] != -1) {
        rootValue[rx] = rootValue[ry] ^ diff[ry];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while (cin >> n >> q && n) {
        caseId++;
        cout << "Case " << caseId << ":\n";
        
        // 初始化
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            diff[i] = 0;
            rootValue[i] = -1;
        }
        
        int facts = 0;            // 已处理的事实数量
        bool conflict = false;    // 是否已发现冲突
        int conflictFact = 0;     // 冲突发生的事实编号
        
        cin.ignore();  // 忽略换行符
        for (int i = 0; i < q; i++) {
            string line;
            getline(cin, line);
            if (conflict) continue;
            
            if (line[0] == 'I') {
                facts++;
                istringstream iss(line);
                char type;
                int p, q, v;
                iss >> type >> p;
                
                if (iss >> q >> v) {
                    // 格式: I p q v
                    if (!merge(p, q, v)) {
                        conflict = true;
                        conflictFact = facts;
                    }
                } else {
                    // 格式: I p v
                    v = q;
                    int r = find(p);
                    int expected = diff[p] ^ v;  // X[r] = X[p] ^ diff[p]
                    
                    if (rootValue[r] != -1) {
                        if (rootValue[r] != expected) {
                            conflict = true;
                            conflictFact = facts;
                        }
                    } else {
                        rootValue[r] = expected;
                    }
                }
            } else if (line[0] == 'Q') {
                istringstream iss(line);
                char type;
                int k;
                iss >> type >> k;
                
                vector<int> vars(k);
                for (int j = 0; j < k; j++) iss >> vars[j];
                
                // 统计每个连通分量的信息
                map<int, int> compXor;  // 分量内查询变量的 diff 异或和
                map<int, int> compCnt;  // 分量内查询变量个数奇偶性
                
                for (int j = 0; j < k; j++) {
                    int x = vars[j];
                    int r = find(x);
                    compXor[r] ^= diff[x];
                    compCnt[r] ^= 1;  // 切换奇偶性
                }
                
                int ans = 0;
                bool unknown = false;
                
                for (auto& entry : compCnt) {
                    int r = entry.first;
                    int parity = entry.second;
                    int diffSum = compXor[r];
                    
                    if (parity) {  // 奇数个变量
                        if (rootValue[r] == -1) {
                            unknown = true;
                            break;
                        }
                        ans ^= rootValue[r] ^ diffSum;
                    } else {  // 偶数个变量
                        ans ^= diffSum;  // X[r] 被消去，只需要 diff 的异或和
                    }
                }
                
                if (unknown) cout << "I don't know.\n";
                else cout << ans << "\n";
            }
        }
        
        if (conflict) {
            cout << "The first " << conflictFact << " facts are conflicting.\n";
        }
        cout << "\n";
    }
    
    return 0;
}
