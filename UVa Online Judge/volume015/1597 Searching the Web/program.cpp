// Searching the Web
// UVa ID: 1597
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 停用词集合
const unordered_set<string> STOP_WORDS = {"the", "a", "to", "and", "or", "not"};

// 将字符串转为小写
string toLowerCase(const string& inputStr) {
    string result = inputStr;
    for (char& ch : result) {
        ch = tolower(ch);
    }
    return result;
}

// 分词函数：按非字母字符切分
vector<string> tokenizeLine(const string& lineText) {
    vector<string> tokens;
    string currentToken;
    for (char ch : lineText) {
        if (isalpha(ch)) {
            currentToken += tolower(ch);
        } else {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
    }
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    return tokens;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int docCount;
    cin >> docCount;
    cin.ignore(); // 忽略换行符

    vector<vector<string>> documents(docCount); // 存储所有文档内容
    unordered_map<string, vector<pair<int, int>>> invertedIndex; // 倒排索引：词 -> [(文档ID, 行号)]

    // 读取并处理所有文档
    for (int docId = 0; docId < docCount; ++docId) {
        string line;
        while (getline(cin, line)) {
            if (line == "**********") break; // 文档结束标记
            documents[docId].push_back(line);
            // 分词并构建索引
            vector<string> words = tokenizeLine(line);
            for (const string& word : words) {
                // 过滤停用词
                if (STOP_WORDS.find(word) == STOP_WORDS.end()) {
                    invertedIndex[word].emplace_back(docId, documents[docId].size() - 1);
                }
            }
        }
    }

    int queryCount;
    cin >> queryCount;
    cin.ignore();

    // 处理每个查询
    for (int queryIdx = 0; queryIdx < queryCount; ++queryIdx) {
        string queryStr;
        getline(cin, queryStr);

        // 根据查询类型分别处理
        if (queryStr.find("AND") != string::npos) {
            // AND 查询：term1 AND term2
            size_t andPos = queryStr.find(" AND ");
            string term1 = queryStr.substr(0, andPos);
            string term2 = queryStr.substr(andPos + 5);

            auto& term1List = invertedIndex[term1];
            auto& term2List = invertedIndex[term2];

            // 标记包含每个词的文档
            vector<bool> hasTerm1(docCount, false), hasTerm2(docCount, false);
            for (const auto& entry : term1List) hasTerm1[entry.first] = true;
            for (const auto& entry : term2List) hasTerm2[entry.first] = true;

            // 找出同时包含两个词的文档
            vector<int> matchingDocs;
            for (int docId = 0; docId < docCount; ++docId) {
                if (hasTerm1[docId] && hasTerm2[docId]) {
                    matchingDocs.push_back(docId);
                }
            }

            // 输出匹配的行
            bool foundMatch = false;
            for (size_t i = 0; i < matchingDocs.size(); ++i) {
                int docId = matchingDocs[i];
                if (i > 0) cout << "----------\n";

                // 收集匹配行并去重
                set<int> matchedLines;
                for (const auto& entry : term1List) {
                    if (entry.first == docId) {
                        matchedLines.insert(entry.second);
                    }
                }
                for (const auto& entry : term2List) {
                    if (entry.first == docId) {
                        matchedLines.insert(entry.second);
                    }
                }

                // 输出匹配行
                for (int lineNum : matchedLines) {
                    cout << documents[docId][lineNum] << '\n';
                    foundMatch = true;
                }
            }
            if (!foundMatch) {
                cout << "Sorry, I found nothing.\n";
            }

        } else if (queryStr.find("OR") != string::npos) {
            // OR 查询：term1 OR term2
            size_t orPos = queryStr.find(" OR ");
            string term1 = queryStr.substr(0, orPos);
            string term2 = queryStr.substr(orPos + 4);

            auto& term1List = invertedIndex[term1];
            auto& term2List = invertedIndex[term2];

            // 标记包含任一词的文档
            vector<bool> matchedDocs(docCount, false);
            for (const auto& entry : term1List) matchedDocs[entry.first] = true;
            for (const auto& entry : term2List) matchedDocs[entry.first] = true;

            vector<int> docsInOrder;
            for (int docId = 0; docId < docCount; ++docId) {
                if (matchedDocs[docId]) docsInOrder.push_back(docId);
            }

            // 输出匹配的行
            bool foundMatch = false;
            for (size_t i = 0; i < docsInOrder.size(); ++i) {
                int docId = docsInOrder[i];
                if (i > 0) cout << "----------\n";

                // 收集匹配行并去重
                set<int> matchedLines;
                for (const auto& entry : term1List) {
                    if (entry.first == docId) {
                        matchedLines.insert(entry.second);
                    }
                }
                for (const auto& entry : term2List) {
                    if (entry.first == docId) {
                        matchedLines.insert(entry.second);
                    }
                }

                // 输出匹配行
                for (int lineNum : matchedLines) {
                    cout << documents[docId][lineNum] << '\n';
                    foundMatch = true;
                }
            }
            if (!foundMatch) {
                cout << "Sorry, I found nothing.\n";
            }

        } else if (queryStr.find("NOT") != string::npos) {
            // NOT 查询：NOT term
            string term = queryStr.substr(4);

            // 标记包含该词的文档
            vector<bool> excludeDocs(docCount, false);
            if (invertedIndex.find(term) != invertedIndex.end()) {
                for (const auto& entry : invertedIndex[term]) {
                    excludeDocs[entry.first] = true;
                }
            }

            // 输出不包含该词的完整文档
            bool foundMatch = false;
            for (int docId = 0; docId < docCount; ++docId) {
                if (!excludeDocs[docId]) {
                    if (foundMatch) cout << "----------\n";
                    for (const string& line : documents[docId]) {
                        cout << line << '\n';
                    }
                    foundMatch = true;
                }
            }
            if (!foundMatch) {
                cout << "Sorry, I found nothing.\n";
            }

        } else {
            // 单个词查询
            string term = queryStr;

            if (invertedIndex.find(term) == invertedIndex.end() || invertedIndex[term].empty()) {
                cout << "Sorry, I found nothing.\n";
            } else {
                auto& termList = invertedIndex[term];

                // 去重并排序
                set<pair<int, int>> uniqueEntries;
                for (const auto& entry : termList) {
                    uniqueEntries.insert(entry);
                }

                // 按文档和行号顺序输出
                int prevDocId = -1;
                for (const auto& entry : uniqueEntries) {
                    int docId = entry.first;
                    int lineNum = entry.second;
                    if (docId != prevDocId) {
                        if (prevDocId != -1) cout << "----------\n";
                        prevDocId = docId;
                    }
                    cout << documents[docId][lineNum] << '\n';
                }
            }
        }

        // 每个查询结果结束标记
        cout << "==========\n";
    }

    return 0;
}
