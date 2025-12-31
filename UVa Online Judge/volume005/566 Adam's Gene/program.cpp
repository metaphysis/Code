// Adam's Gene
// UVa ID: 566
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Clone {
    string parent;                     // 父克隆体名称
    unordered_set<string> mutations;   // 本克隆体新增的突变基因
    vector<string> mutationOrder;      // 保持突变基因的顺序
    unordered_map<string, int> geneCount; // 从祖先继承的基因计数（包括自身）
    bool consistent;                   // 是否与ADAM相连
};

unordered_map<string, Clone> clones;   // 记录所有已处理的克隆体

// 检查克隆请求是否安全，返回首个出现两次的基因，若安全则返回空字符串
string checkSafety(const Clone& curr) {
    // 按照突变列表中出现的顺序检查每个基因
    for (const string& gene : curr.mutationOrder) {
        auto it = curr.geneCount.find(gene);
        if (it != curr.geneCount.end() && it->second >= 2) 
            return gene;
    }
    return "";
}

// 处理一个克隆请求
void processRequest(const string& line) {
    stringstream ss(line);
    string dummy, child, from, parent;
    ss >> dummy >> child >> from >> parent;

    // 解析突变基因，保持顺序
    vector<string> newMutationOrder;
    unordered_set<string> newMutations;
    string mutating;
    if (ss >> mutating && mutating == "mutating") {
        string gene;
        while (ss >> gene) {
            newMutationOrder.push_back(gene);
            newMutations.insert(gene);
        }
    }

    // 输出原始请求部分
    cout << "clone " << child << " from " << parent;

    // 如果父克隆体不存在或不一致，则子克隆也不一致
    if (parent != "ADAM" && !clones.count(parent)) {
        cout << " has no connection to ADAM\n";
        clones[child] = {parent, newMutations, newMutationOrder, {}, false};
        return;
    }

    Clone& parentClone = clones[parent];
    if (!parentClone.consistent) {
        cout << " has no connection to ADAM\n";
        clones[child] = {parent, newMutations, newMutationOrder, {}, false};
        return;
    }

    // 构建当前克隆体的基因计数
    Clone curr = {parent, newMutations, newMutationOrder, parentClone.geneCount, true};
    for (const string& gene : newMutationOrder) 
        curr.geneCount[gene]++;

    // 检查安全性 - 检查所有基因，不仅仅是新增的
    string unsafeGene = checkSafety(curr);
    if (!unsafeGene.empty()) {
        cout << " was at least twice mutated with " << unsafeGene << "\n";
        clones[child] = {parent, newMutations, newMutationOrder, {}, false}; // 不安全视为不一致
        return;
    }

    // 一致且安全
    cout << " is consistent and safe\n";
    clones[child] = curr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化ADAM
    clones["ADAM"] = {"", {}, {}, {}, true};

    string line;
    while (getline(cin, line)) 
        processRequest(line);

    return 0;
}
