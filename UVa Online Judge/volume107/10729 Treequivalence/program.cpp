// Treequivalence
// UVa ID: 10729
// Verdict: Accepted
// Submission Date: 2026-01-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 256;
vector<int> g[256];       // 邻接表，存储每个节点的子节点
int parent[MAXN], label[MAXN], cnt;  // 父节点，节点标签，节点计数
string s1, s2;            // 输入的两个字符串

// 递归解析字符串构建树，返回当前节点的索引
int build(int& p, int father) {
    int idx = cnt++;                     // 分配新节点ID
    label[idx] = s1[p++], parent[idx] = father;  // 记录标签和父节点
    if (p < s1.size() && s1[p] == '(') { // 如果有子节点
        p++;                              // 跳过'('
        while (true) {
            int childIdx = build(p, idx); // 递归构建子节点
            g[idx].push_back(childIdx);   // 添加到邻接表
            char c = s1[p];
            if (c == ',' || c == ')') p++; // 跳过分隔符
            if (c == ')') break;          // 子节点列表结束
        }
    }
    return idx;
}

// DFS生成子树字符串，forbidden表示要排除的父节点
string dfs(int u, int forbidden) {
    string self = string(1, label[u]), child;
    for (auto v : g[u])
        if (v != forbidden) {            // 排除父节点
            if (child.size()) child += ',';
            child += dfs(v, u);          // 递归生成子节点字符串
        }
    if (child.size()) return self + '(' + child + ')';  // 有子节点时加括号
    return self;                         // 叶子节点
}

// 生成从节点u看向其子节点child方向的子树字符串（逆时针顺序）
string getRotation(int u, int child) {
    string self = string(1, label[u]), father;
    if (parent[u] != -1) father = getRotation(parent[u], u);  // 递归处理父节点
    vector<string> left, right;          // 存储child左边和右边的子树字符串
    for (auto v : g[u]) {
        string tmp = dfs(v, -1);         // 生成子树完整字符串
        if (v < child) left.push_back(tmp);   // child之前的子节点
        if (v > child) right.push_back(tmp);  // child之后的子节点
    }
    right.push_back(father);             // 父节点放在right末尾
    for (auto s : left) right.push_back(s); // left部分接在最后
    string children;
    for (auto s : right)
        if (s.size()) {
            if (children.size()) children += ',';
            children += s;
        }
    if (children.size()) self = self + '(' + children + ')';  // 拼接结果
    return self;
}

// 验证两棵树是否等价
bool validate() {
    for (int i = 0; i < MAXN; i++) g[i].clear();  // 清空邻接表
    cnt = 0;                     // 重置节点计数
    int idx = 0;
    build(idx, -1);              // 构建第一棵树
    for (int i = 0; i < cnt; i++) {  // 枚举每个节点作为新根
        string self = string(1, label[i]), father;
        if (parent[i] != -1) father = getRotation(parent[i], i);  // 生成父节点方向字符串
        vector<string> children;      // 存储所有子节点（包括可能的父节点）
        for (auto v : g[i]) {
            string tmp = dfs(v, -1);  // 生成子节点字符串
            children.push_back(tmp);
        }
        if (father.size()) children.push_back(father);  // 添加父节点（如果存在）
        if (children.size()) {
            int n = children.size();
            // 尝试所有循环移位顺序（根节点的子节点可以旋转）
            for (int start = 0; start < n; start++) {
                string s3;
                for (int j = 0; j < n; j++) {
                    if (s3.size()) s3 += ',';
                    s3 += children[(start + j) % n];  // 循环移位
                }
                if (s3.size()) s3 = self + '(' + s3 + ')';  // 构造完整字符串
                if (s3 == s2) return true;           // 与第二棵树匹配
            }
        } else if (self == s2) return true;          // 单节点树的情况
    }
    return false;  // 所有可能性都不匹配
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> s1 >> s2;
        cout << (validate() ? "same" : "different") << '\n';
    }
    return 0;
}
