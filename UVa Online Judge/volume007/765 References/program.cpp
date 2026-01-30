// References
// UVa ID: 765
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 检查一行是否为空行（只包含空格或无字符）
bool isEmptyLine(const string& s) {
    return all_of(s.begin(), s.end(), ::isspace);
}

// 从字符串中提取参考文献编号，如"[23]"返回23
int extractRefNum(const string& s) {
    if (s.empty() || s[0] != '[') return -1;
    int num = 0;
    for (size_t i = 1; i < s.size() && s[i] != ']'; ++i) 
        if (isdigit(s[i])) num = num * 10 + (s[i] - '0');
    return num;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 读取所有行
    vector<string> lines;
    string line;
    while (getline(cin, line)) 
        lines.push_back(line);
    
    // 分割段落：根据空行分隔
    vector<vector<string>> paragraphs;
    vector<string> curPara;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (isEmptyLine(lines[i])) {
            if (!curPara.empty()) paragraphs.push_back(curPara);
            curPara.clear();
            // 跳过连续的空行
            while (i + 1 < lines.size() && isEmptyLine(lines[i + 1])) i++;
        } else curPara.push_back(lines[i]);
    }
    if (!curPara.empty()) paragraphs.push_back(curPara);
    
    // 识别段落类型并收集信息
    vector<vector<string>> regularParas;  // 常规段落
    vector<pair<int, vector<string>>> refDescs;  // 参考文献描述段落(旧编号, 内容)
    regex refPat(R"(\[(\d+)\])");  // 匹配引用的正则表达式
    vector<int> firstOrder;  // 引用首次出现的顺序
    unordered_set<int> seenRefs;  // 已经出现过的引用编号
    
    for (const auto& para : paragraphs) {
        // 参考文献描述段落：第一行以'['开头
        if (!para.empty() && para[0][0] == '[') {
            int refNum = extractRefNum(para[0]);
            if (refNum > 0) refDescs.emplace_back(refNum, para);
        } else {
            // 常规段落
            regularParas.push_back(para);
            // 提取其中的所有引用编号，记录首次出现顺序
            for (const string& line : para) {
                auto start = line.cbegin();
                smatch match;
                while (regex_search(start, line.cend(), match, refPat)) {
                    int refNum = stoi(match[1]);
                    if (seenRefs.insert(refNum).second) 
                        firstOrder.push_back(refNum);
                    start = match.suffix().first;
                }
            }
        }
    }
    
    // 建立旧编号到新编号的映射
    unordered_map<int, int> oldToNew;
    for (size_t i = 0; i < firstOrder.size(); ++i) 
        oldToNew[firstOrder[i]] = i + 1;
    
    // 输出常规段落，更新引用编号
    bool first = true;
    for (const auto& para : regularParas) {
        if (!first) cout << "\n\n";
        first = false;
        for (size_t i = 0; i < para.size(); ++i) {
            if (i > 0) cout << "\n";
            string line = para[i];
            auto start = line.cbegin();
            smatch match;
            // 替换行中的所有引用编号
            while (regex_search(start, line.cend(), match, refPat)) {
                cout << string(start, match[0].first);
                int oldNum = stoi(match[1]);
                cout << "[" << oldToNew[oldNum] << "]";
                start = match.suffix().first;
            }
            cout << string(start, line.cend());
        }
    }
    
    // 处理参考文献描述段落：更新编号并排序
    vector<pair<int, vector<string>>> updatedDescs;
    for (auto& desc : refDescs) {
        int oldNum = desc.first;
        if (!oldToNew.count(oldNum)) continue;  // 跳过没有被引用的描述
        int newNum = oldToNew[oldNum];
        vector<string> newDesc = desc.second;
        // 更新第一行的编号
        size_t pos = newDesc[0].find(']');
        if (pos != string::npos) 
            newDesc[0] = "[" + to_string(newNum) + "]" + newDesc[0].substr(pos + 1);
        updatedDescs.emplace_back(newNum, newDesc);
    }
    
    // 按新编号排序
    sort(updatedDescs.begin(), updatedDescs.end());
    
    // 输出参考文献描述段落
    for (const auto& desc : updatedDescs) {
        if (!first) cout << "\n\n";
        first = false;
        const auto& lines = desc.second;
        for (size_t i = 0; i < lines.size(); ++i) {
            if (i > 0) cout << "\n";
            cout << lines[i];
        }
    }
    
    if (!first) cout << "\n";
    return 0;
}
