// Cheapest Scores
// UVa ID: 351
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Event {
    string name;
    int score;
    string prereqName;
    int parent;
    vector<int> children;
};

struct Sequence {
    int totalScore;
    vector<int> counts;   // 长度为事件数
};

struct Game {
    vector<Event> events;
    vector<int> queries;
};

// 生成每个事件的序列（从根到该事件的路径）
void buildSequences(const vector<Event>& events, vector<Sequence>& seqs) {
    int n = events.size();
    seqs.assign(n, Sequence{0, vector<int>(n, 0)});
    vector<int> roots;
    for (int i = 0; i < n; ++i)
        if (events[i].parent == -1) roots.push_back(i);

    function<void(int, vector<int>&)> dfs = [&](int u, vector<int>& path) {
        path.push_back(u);
        // 生成当前节点的序列
        int total = 0;
        vector<int> cnt(n, 0);
        for (int idx : path) {
            total += events[idx].score;
            cnt[idx]++;
        }
        seqs[u] = {total, cnt};
        // 递归子节点
        for (int v : events[u].children)
            dfs(v, path);
        path.pop_back();
    };

    for (int r : roots) {
        vector<int> path;
        dfs(r, path);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Game> games;
    int N;
    while (cin >> N && N != 0) {
        cin.ignore(); // 忽略 N 后的换行
        Game game;
        game.events.resize(N);
        for (int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            string name, prereq;
            int score;
            iss >> name >> score;
            game.events[i].name = name;
            game.events[i].score = score;
            if (iss >> prereq)
                game.events[i].prereqName = prereq;
            else
                game.events[i].prereqName = "";
        }
        int x;
        while (cin >> x && x != 0)
            game.queries.push_back(x);
        games.push_back(game);
    }

    int totalCases = 0;
    for (const auto& g : games)
        totalCases += g.queries.size();

    int caseIdx = 0;
    for (int gNum = 1; gNum <= (int)games.size(); ++gNum) {
        Game& game = games[gNum - 1];
        int n = game.events.size();

        // 建立名称到索引的映射
        unordered_map<string, int> nameToIdx;
        for (int i = 0; i < n; ++i)
            nameToIdx[game.events[i].name] = i;

        // 确定父节点并构建孩子列表
        for (int i = 0; i < n; ++i) {
            if (game.events[i].prereqName.empty())
                game.events[i].parent = -1;
            else
                game.events[i].parent = nameToIdx[game.events[i].prereqName];
            game.events[i].children.clear();
        }
        for (int i = 0; i < n; ++i) {
            int p = game.events[i].parent;
            if (p != -1)
                game.events[p].children.push_back(i);
        }

        // 生成所有序列（每个事件对应一个）
        vector<Sequence> seqs;
        buildSequences(game.events, seqs);

        // 收集可用物品（总分 > 0）
        vector<Sequence> items;
        int maxScore = 0;
        for (int s : game.queries)
            maxScore = max(maxScore, s);

        for (int i = 0; i < n; ++i) {
            if (seqs[i].totalScore > 0 && seqs[i].totalScore <= maxScore)
                items.push_back(seqs[i]);
        }

        // 完全背包：dp[j] = 最小序列数，pre[j] = 最后使用的物品编号
        const int INF = 1e9;
        vector<int> dp(maxScore + 1, INF);
        vector<int> pre(maxScore + 1, -1);
        dp[0] = 0;

        for (int i = 0; i < (int)items.size(); ++i) {
            int w = items[i].totalScore;
            for (int j = w; j <= maxScore; ++j) {
                if (dp[j - w] != INF && dp[j - w] + 1 < dp[j]) {
                    dp[j] = dp[j - w] + 1;
                    pre[j] = i;
                }
            }
        }

        // 处理每个查询
        for (int qIdx = 1; qIdx <= (int)game.queries.size(); ++qIdx) {
            int score = game.queries[qIdx - 1];
            ++caseIdx;

            if (dp[score] == INF) {
                cout << "Case " << gNum << "." << qIdx << " (" << score << "):\n      This score is impossible.\n";
            } else {
                // 回溯得到每种事件的总次数
                vector<int> totalCnt(n, 0);
                int cur = score;
                while (cur > 0) {
                    int itemIdx = pre[cur];
                    for (int i = 0; i < n; ++i)
                        totalCnt[i] += items[itemIdx].counts[i];
                    cur -= items[itemIdx].totalScore;
                }

                cout << "Case " << gNum << "." << qIdx << " (" << score << "):\n";
                string line;
                for (int i = 0; i < n; ++i) {
                    if (totalCnt[i] == 0) continue;
                    if (!line.empty()) line += "\n";
                    line += "      " + to_string(totalCnt[i]) + " " + game.events[i].name;
                    if (totalCnt[i] > 1) line += "s";
                    line += " (" + to_string(game.events[i].score * totalCnt[i]) + ")";
                }
                cout << line << "\n";
            }

            // 除最后一个 case 外，输出空行
            if (caseIdx < totalCases)
                cout << "\n";
        }
    }

    return 0;
}
