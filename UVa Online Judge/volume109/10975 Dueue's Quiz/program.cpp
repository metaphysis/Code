// Dueue's Quiz
// UVa ID: 10975
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.450s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    array<int, 26> next;
    int fail;
    Node() { next.fill(-1); fail = 0; }
};

class ACAutomaton {
public:
    vector<Node> trie;
    vector<int> bfsOrder;   // BFS 顺序（不含根），用于逆序累加 fail
    ACAutomaton() { trie.emplace_back(); }
    // 插入单词，返回结束节点编号
    int insert(const string& s) {
        int cur = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[cur].next[c] == -1) {
                trie[cur].next[c] = (int)trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].next[c];
        }
        return cur;
    }
    // 构建 fail 指针并补全转移表，同时记录 BFS 顺序
    void build() {
        queue<int> q;
        bfsOrder.clear();
        // 处理根节点的孩子
        for (int c = 0; c < 26; ++c) {
            int &nxt = trie[0].next[c];
            if (nxt != -1) {
                trie[nxt].fail = 0;
                q.push(nxt);
            } else {
                nxt = 0;        // 补全为根
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            bfsOrder.push_back(u);
            for (int c = 0; c < 26; ++c) {
                int &v = trie[u].next[c];
                if (v != -1) {
                    trie[v].fail = trie[ trie[u].fail ].next[c];
                    q.push(v);
                } else {
                    v = trie[ trie[u].fail ].next[c];
                }
            }
        }
    }
    // 匹配文本串，更新 cnt 数组（每个状态出现次数加 1）
    void match(const string& text, vector<int>& cnt) const {
        int state = 0;
        for (char ch : text) {
            int c = ch - 'a';
            state = trie[state].next[c];
            ++cnt[state];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int D;
        cin >> D;
        unordered_map<string, int> wordToNode;   // 去重，记录每个单词对应的节点
        ACAutomaton ac;
        for (int i = 0; i < D; ++i) {
            string w;
            cin >> w;
            if ((int)w.length() > 100) continue;   // 长度超过100不可能出现
            if (wordToNode.find(w) == wordToNode.end()) {
                int node = ac.insert(w);
                wordToNode[w] = node;
            }
        }
        ac.build();
        int Q;
        cin >> Q;
        cout << "Test Case #" << tc << '\n';
        for (int q = 1; q <= Q; ++q) {
            int M, N;
            cin >> M >> N;
            vector<string> table(M);
            for (int i = 0; i < M; ++i) cin >> table[i];
            vector<int> cnt(ac.trie.size(), 0);
            // 1. 水平方向：每一行正向和反向
            for (int i = 0; i < M; ++i) {
                string s = table[i];
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            // 2. 垂直方向：每一列正向和反向
            for (int j = 0; j < N; ++j) {
                string s;
                s.reserve(M);
                for (int i = 0; i < M; ++i) s.push_back(table[i][j]);
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            // 3. 主对角线（方向 (1,1)）
            // 起点：第一行 (0, j) 和第一列 (i,0)，避免重复 (0,0)
            for (int j = 0; j < N; ++j) {
                string s;
                int i = 0, col = j;
                while (i < M && col < N) {
                    s.push_back(table[i][col]);
                    ++i; ++col;
                }
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            for (int i = 1; i < M; ++i) {
                string s;
                int row = i, col = 0;
                while (row < M && col < N) {
                    s.push_back(table[row][col]);
                    ++row; ++col;
                }
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            // 4. 副对角线（方向 (1,-1)）
            // 起点：第一行 (0, j) 和最后一列 (i, N-1)，避免重复 (0, N-1)
            for (int j = 0; j < N; ++j) {
                string s;
                int i = 0, col = j;
                while (i < M && col >= 0) {
                    s.push_back(table[i][col]);
                    ++i; --col;
                }
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            for (int i = 1; i < M; ++i) {
                string s;
                int row = i, col = N - 1;
                while (row < M && col >= 0) {
                    s.push_back(table[row][col]);
                    ++row; --col;
                }
                ac.match(s, cnt);
                reverse(s.begin(), s.end());
                ac.match(s, cnt);
            }
            // 沿着 fail 树自底向上累加次数
            for (int i = (int)ac.bfsOrder.size() - 1; i >= 0; --i) {
                int u = ac.bfsOrder[i];
                cnt[ ac.trie[u].fail ] += cnt[u];
            }
            // 收集出现过（cnt > 0）的单词，按字典序排序
            vector<pair<string, int>> ans;
            for (const auto& p : wordToNode) {
                int node = p.second;
                if (cnt[node] > 0) ans.emplace_back(p.first, cnt[node]);
            }
            sort(ans.begin(), ans.end());
            cout << "Query #" << q << '\n';
            for (const auto& p : ans) {
                cout << p.first << ' ' << p.second << '\n';
            }
        }
        cout << '\n';   // 每个测试用例后输出空行
    }
    return 0;
}
