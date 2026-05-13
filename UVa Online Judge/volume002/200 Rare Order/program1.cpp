// Rare Order
// UVa ID: 200
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 26;  // 大写字母共26个

vector<int> g[MAXV];  // 邻接表
int degreeOfIn[MAXV]; // 入度
int visited[MAXV];    // 标记字母是否出现过

int main() {
    string word;
    vector<string> words;

    while (getline(cin, word)) {
        if (word != "#") {
            words.push_back(word); // 存储输入字符串
            continue;
        }

        // 初始化
        for (int u = 0; u < MAXV; u++) g[u].clear();
        memset(degreeOfIn, 0, sizeof(degreeOfIn));
        memset(visited, 0, sizeof(visited));

        // 依据相邻字符串推断字符顺序关系
        for (int i = 0; i < words.size() - 1; i++) {
            string &a = words[i];
            string &b = words[i + 1];
            for (int j = 0; j < min(a.length(), b.length()); j++) {
                int u = a[j] - 'A';
                int v = b[j] - 'A';
                visited[u] = visited[v] = 1; // 标记两个字母都出现过
                if (u != v) {
                    g[u].push_back(v);  // u 排在 v 之前
                    degreeOfIn[v]++;
                    break; // 只考虑第一个不同的位置
                }
            }
        }

        // 拓扑排序：队列实现 Kahn 算法
        queue<int> q;
        for (int u = 0; u < MAXV; u++)
            if (visited[u] && degreeOfIn[u] == 0)
                q.push(u);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u])
                if (--degreeOfIn[v] == 0)
                    q.push(v);
            cout << (char)('A' + u);
        }
        cout << '\n';
        words.clear(); // 清空，准备处理下一组数据
    }
    return 0;
}
