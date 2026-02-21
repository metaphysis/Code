// Sub-Expression Counting
// UVa ID: 12942
// Verdict: Accepted
// Submission Date: 2026-02-09
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull HA = 63689ULL, HB = 378551ULL;

// 叶子节点哈希值固定为1（AC代码的做法）
const ull LEAF_HASH = 1ULL;

// 解析表达式并收集哈希值
ull parse(const string& s, int& pos, vector<ull>& hashes) {
    if (s[pos] != '(') {
        // 叶子节点：变量或数字，统一哈希为1
        hashes.push_back(LEAF_HASH);
        // 跳过整个操作数
        while (pos < s.size() && s[pos] != ')' && s[pos] != '+' && 
               s[pos] != '-' && s[pos] != '*' && s[pos] != '/')
            pos++;
        return LEAF_HASH;
    }
    // 内部节点：( expr op expr )
    pos++; // 跳过 '('
    // 解析左子树
    ull leftHash = parse(s, pos, hashes);
    // 跳过运算符
    pos++;
    // 解析右子树
    ull rightHash = parse(s, pos, hashes);
    // 跳过 ')'
    pos++;
    // 哈希算法
    ull hash = 0ULL;
    hash = hash * HA + leftHash;
    ull currentHa = HA * HB;
    hash = hash * currentHa + rightHash;
    currentHa *= HB;
    hash = hash * currentHa + 1ULL;
    hashes.push_back(hash);
    return hash;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string alpha, beta;
    while (cin >> alpha >> beta) {
        // 解析α获取目标哈希值
        vector<ull> alphaHashes;
        int pos = 0;
        parse(alpha, pos, alphaHashes);
        ull targetHash = alphaHashes.back();
        // 解析β并统计匹配数
        vector<ull> betaHashes;
        pos = 0;
        parse(beta, pos, betaHashes);
        int cnt = 0;
        for (ull h : betaHashes)
            if (h == targetHash) cnt++;
        cout << cnt << "\n";
    }
    return 0;
}
