// Last Name First Please
// UVa ID: 597
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 1.810s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct File {
    string original;   // 原始名称
    string newName;    // 新名称
};

int n;
vector<File> files;

// DFS：mask 已重命名集合，curId 当前选中的文件 ID，path 记录重命名顺序
bool dfs(int mask, int curId, vector<int>& path) {
    if (mask == (1 << n) - 1) return true;
    // 按当前文件名排序，得到列表顺序
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        string nameA = (mask & (1 << a)) ? files[a].newName : files[a].original;
        string nameB = (mask & (1 << b)) ? files[b].newName : files[b].original;
        return nameA < nameB;
    });
    // 找到当前文件在列表中的位置
    int pos = find(order.begin(), order.end(), curId) - order.begin();
    // 收集相邻且未重命名的候选文件
    vector<int> candidates;
    if (pos > 0) {
        int id = order[pos - 1];
        if (!(mask & (1 << id))) candidates.push_back(id);
    }
    if (pos + 1 < n) {
        int id = order[pos + 1];
        if (!(mask & (1 << id))) candidates.push_back(id);
    }
    // 尝试每个候选
    for (int id : candidates) {
        path.push_back(id);
        if (dfs(mask | (1 << id), id, path)) return true;
        path.pop_back();
    }
    return false;
}

// 处理单个测试用例
void processCase(const vector<string>& rawLines) {
    n = (int)rawLines.size();
    files.resize(n);
    // 解析每个文件名
    for (int i = 0; i < n; ++i) {
        const string& s = rawLines[i];
        size_t spacePos = s.find(' ');
        size_t dotPos = s.rfind('.');
        string first = s.substr(0, spacePos);
        string last = s.substr(spacePos + 1, dotPos - spacePos - 1);
        string ext = s.substr(dotPos);          // 保留扩展名（如 .jpg）
        files[i].original = s;
        files[i].newName = last + ", " + first + ext;
    }
    // 按原始文件名排序（初始列表顺序）
    sort(files.begin(), files.end(), [](const File& a, const File& b) {
        return a.original < b.original;
    });
    // 从第一个文件开始重命名（索引 0）
    vector<int> path;
    path.push_back(0);
    int mask = 1 << 0;
    bool ok = (n == 1) ? true : dfs(mask, 0, path);  // 若只有一个文件则直接成功
    // 输出结果（全局控制用例间空行）
    static bool firstOutput = true;
    if (!firstOutput) cout << '\n';
    firstOutput = false;
    if (!ok) cout << "NO QUICK RENAMING POSSIBLE\n";
    } else {
        for (int id : path)
            cout << files[id].newName << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<string> currentLines;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (!currentLines.empty()) {
                processCase(currentLines);
                currentLines.clear();
            }
            // 忽略多余空行
        } else currentLines.push_back(line);
    }
    // 处理最后一个用例（可能没有结尾空行）
    if (!currentLines.empty()) processCase(currentLines);
    return 0;
}
