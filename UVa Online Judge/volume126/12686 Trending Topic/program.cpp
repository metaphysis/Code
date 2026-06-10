// Trending Topic
// UVa ID: 12686
// Verdict: Accepted
// Submission Date: 2026-06-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 处理一天内的文本，统计该天每个单词的频次
unordered_map<string, int> processDay(const string& text) {
    unordered_map<string, int> dayFreq;
    string word;
    for (char c : text) {
        if (islower(c)) {
            word += c;
        } else {
            if (word.size() >= 4) dayFreq[word]++;
            word.clear();
        }
    }
    if (word.size() >= 4) dayFreq[word]++;
    return dayFreq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    queue<unordered_map<string, int>> dayQueue; // 存储每一天的词频
    unordered_map<string, int> globalFreq;      // 最近7天的总词频

    string line;
    string currentText;
    bool inText = false;

    while (getline(cin, line)) {
        // 处理 <text> 开始标签
        if (line.find("<text>") != string::npos) {
            inText = true;
            size_t pos = line.find("<text>");
            string remaining = line.substr(pos + 6);
            // 如果同一行内还有内容
            if (!remaining.empty() && remaining.find("</text>") == string::npos) {
                currentText += ' ' + remaining;
            }
            continue;
        }

        // 处理 </text> 结束标签
        if (line.find("</text>") != string::npos && inText) {
            size_t pos = line.find("</text>");
            string beforeEnd = line.substr(0, pos);
            currentText += ' ' + beforeEnd;

            // 处理这一天的文本
            auto dayFreq = processDay(currentText);
            dayQueue.push(dayFreq);
            for (auto& p : dayFreq) globalFreq[p.first] += p.second;

            // 超过7天，移除最早一天
            if (dayQueue.size() > 7) {
                auto& oldest = dayQueue.front();
                for (auto& p : oldest) {
                    globalFreq[p.first] -= p.second;
                    if (globalFreq[p.first] == 0) globalFreq.erase(p.first);
                }
                dayQueue.pop();
            }

            // 重置状态
            currentText.clear();
            inText = false;
            continue;
        }

        // 在 <text> 和 </text> 之间，累加内容
        if (inText) {
            currentText += ' ' + line;
        }

        // 处理 <top N /> 查询（可能出现在文本之间或之后）
        if (line.find("<top") != string::npos && line.find("/>") != string::npos) {
            int N = 0;
            stringstream ss(line);
            string token;
            while (ss >> token) {
                if (token == "<top") {
                    ss >> N;
                    break;
                }
            }
            if (N == 0) continue;

            // 将 globalFreq 转为 vector 排序
            vector<pair<string, int>> freqList(globalFreq.begin(), globalFreq.end());
            sort(freqList.begin(), freqList.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });

            // 输出结果
            cout << "<top " << N << ">\n";
            int lastFreq = -1;
            int printed = 0;
            for (size_t i = 0; i < freqList.size(); i++) {
                if (printed >= N && freqList[i].second != lastFreq) break;
                cout << freqList[i].first << " " << freqList[i].second << '\n';
                lastFreq = freqList[i].second;
                printed++;
            }
            cout << "</top>\n";
        }
    }

    return 0;
}
