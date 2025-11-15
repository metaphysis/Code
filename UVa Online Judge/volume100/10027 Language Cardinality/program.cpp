// Language Cardinality
// UVa ID: 10027
// Verdict: Accepted
// Submission Date: 2025-11-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string extractString(const string& quoted) {
    if (quoted.size() >= 2 && quoted[0] == '"' && quoted[quoted.size() - 1] == '"')
        return quoted.substr(1, quoted.size() - 2);
    return quoted;
}

struct RuleInfo {
    string left;
    string right;
    RuleInfo(const string& l, const string& r) : left(l), right(r) {}
};

// 自定义优先队列比较函数，优先处理较短的字符串
struct cmp {
    bool operator()(const string& a, const string& b) {
        return a.length() > b.length(); // 最小堆，短字符串优先
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount;
    cin >> caseCount;
    cin.ignore();
    for (int caseNum = 0; caseNum < caseCount; ++caseNum) {
        if (caseNum > 0) cout << endl;
        string line;
        while (getline(cin, line) && line.empty()) {}
        string initialString = extractString(line);
        bool unlimited = false;
        vector<RuleInfo> rules;
        while (getline(cin, line)) {
            if (line.empty()) break;
            if (line.find("->") == string::npos) continue;
            size_t pos = line.find("->");
            string left = extractString(line.substr(0, pos));
            string right = extractString(line.substr(pos + 2));
            if (left == right) continue;
            if (left.empty() && !right.empty()) unlimited = true;
            if (right.find(left) != right.npos) unlimited = true;
            rules.emplace_back(left, right);
        }
        // 检查无限生成规则
        if (unlimited) {
            cout << "Too many." << '\n';
            continue;
        }
        set<string> generatedStrings;
        priority_queue<string, vector<string>, cmp> bfsQueue;
        generatedStrings.insert(initialString);
        bfsQueue.push(initialString);
        while (!bfsQueue.empty() && generatedStrings.size() <= 1000) {
            string current = bfsQueue.top();
            bfsQueue.pop();
            // 对每个规则进行顺序查找和替换
            for (const auto& rule : rules) {
                size_t pos = 0;
                while ((pos = current.find(rule.left, pos)) != string::npos) {
                    // 生成新字符串
                    string newString = current.substr(0, pos) + rule.right + 
                                      current.substr(pos + rule.left.length());
                    if (generatedStrings.find(newString) == generatedStrings.end()) {
                        generatedStrings.insert(newString);
                        bfsQueue.push(newString);
                        if (generatedStrings.size() > 1000) goto output;
                    }
                    pos += 1; // 继续查找下一个匹配位置
                }
            }
        }
        output:
        if (generatedStrings.size() > 1000) cout << "Too many." << '\n';
        else cout << generatedStrings.size() << '\n';
    }
    return 0;
}
