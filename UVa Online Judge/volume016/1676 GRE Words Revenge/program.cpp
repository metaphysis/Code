// GRE Words Revenge
// UVa ID: 1676
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

// AC自动机组
struct Group {
    vector<string> words;                 // 本组所有单词
    vector<array<int, 2>> nxt;            // Trie转移边
    vector<int> fail, val;                // fail指针，val[u]=fail链上终止节点数

    // 构建Trie和fail
    void build() {
        nxt.clear(); fail.clear(); val.clear();
        nxt.push_back({-1, -1});          // 根节点0
        fail.push_back(0);
        val.push_back(0);

        // 插入所有单词
        for (const string& w : words) {
            int u = 0;
            for (char c : w) {
                int b = c - '0';
                if (nxt[u][b] == -1) {
                    nxt[u][b] = (int)nxt.size();
                    nxt.push_back({-1, -1});
                    fail.push_back(0);
                    val.push_back(0);
                }
                u = nxt[u][b];
            }
            val[u] = 1;   // 标记终止节点（由于去重，此处直接置1）
        }

        // BFS构建fail并补边
        queue<int> q;
        for (int b = 0; b < 2; ++b) {
            int v = nxt[0][b];
            if (v != -1) {
                fail[v] = 0;
                // val[v] 已在插入时设为1，但需加上fail的val
                q.push(v);
            } else {
                nxt[0][b] = 0;    // 缺边补0
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            // 计算当前节点的真正val（包含fail链）
            // 注意：根节点的val始终为0，子节点在入队时已设初值，但需加上fail的val
            for (int b = 0; b < 2; ++b) {
                int v = nxt[u][b];
                if (v != -1) {
                    fail[v] = nxt[fail[u]][b];
                    val[v] += val[fail[v]];   // 加上fail链上的终止数
                    q.push(v);
                } else {
                    nxt[u][b] = nxt[fail[u]][b]; // 补边
                }
            }
        }
    }

    // 查询文本s中本组所有单词出现总次数
    long long query(const string& s) const {
        long long res = 0;
        int u = 0;
        for (char c : s) {
            int b = c - '0';
            u = nxt[u][b];
            res += val[u];
        }
        return res;
    }
};

// 解密：加密串enc为原始串循环右移shift位，解密即循环左移shift位
string decrypt(const string& enc, long long shift) {
    int len = (int)enc.size();
    if (len == 0) return enc;
    int k = (int)(shift % len);
    if (k == 0) return enc;
    return enc.substr(k) + enc.substr(0, k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        cout << "Case #" << tc << ":\n";

        long long L = 0;                      // 上次'?'答案
        unordered_set<string> learned;        // 已学单词集合（去重）
        vector<Group> groups;                 // 二进制分组

        for (int i = 0; i < N; ++i) {
            string op;
            cin >> op;
            char cmd = op[0];
            string enc = op.substr(1);
            string orig = decrypt(enc, L);    // 得到原始串

            if (cmd == '+') {
                if (learned.find(orig) == learned.end()) {
                    learned.insert(orig);

                    // 新建大小为1的组
                    Group g;
                    g.words.push_back(orig);
                    g.build();
                    groups.push_back(std::move(g));

                    // 合并大小相同的相邻组（二进制加法）
                    while (groups.size() >= 2 &&
                           groups[groups.size() - 1].words.size() ==
                           groups[groups.size() - 2].words.size()) {
                        Group g1 = std::move(groups.back()); groups.pop_back();
                        Group g2 = std::move(groups.back()); groups.pop_back();

                        Group ng;
                        ng.words.reserve(g1.words.size() + g2.words.size());
                        ng.words.insert(ng.words.end(), g1.words.begin(), g1.words.end());
                        ng.words.insert(ng.words.end(), g2.words.begin(), g2.words.end());
                        ng.build();
                        groups.push_back(std::move(ng));
                    }
                }
            } else { // '?'
                long long ans = 0;
                for (const Group& g : groups)
                    ans += g.query(orig);
                cout << ans << '\n';
                L = ans;   // 更新L供后续解密
            }
        }
    }
    return 0;
}
