#include <bits/stdc++.h>
using namespace std;

// 后缀自动机节点
struct State {
    int len;          // 该状态能接受的最长子串长度
    int link;         // 后缀链接
    int occ;          // 出现次数
    map<char, int> next; // 转移边
    State() : len(0), link(-1), occ(0) {}
};

// 后缀自动机类
class SuffixAutomaton {
private:
    vector<State> st;  // 状态数组
    int last;          // 最后一个状态
    long long answer;  // 答案

public:
    SuffixAutomaton() {
        st.push_back(State()); // 初始状态
        st[0].len = 0;
        st[0].link = -1;
        last = 0;
        answer = 0;
    }

    // 扩展字符
    void extend(char c) {
        int cur = st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].occ = 1;
        int p = last;
        // 为路径上的状态添加转移，同时寻找第一个有c转移的状态
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]); // 复制状态
                st[clone].len = st[p].len + 1;
                st[clone].occ = 0;   // 新状态的出现次数初始为0
                // 重定向p到q的路径到clone
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // 计算答案
    long long computeAnswer() {
        int n = st.size();
        // 按len排序，用于拓扑统计出现次数
        vector<int> cnt(n + 1, 0), order(n, 0);
        for (int i = 0; i < n; i++) cnt[st[i].len]++;
        for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) order[--cnt[st[i].len]] = i;
        // 按len从大到小累加出现次数
        for (int i = n - 1; i > 0; i--) {
            int v = order[i];
            st[st[v].link].occ += st[v].occ;
        }
        // 统计出现次数>=2的状态贡献的子串数
        for (int i = 1; i < n; i++) {
            if (st[i].occ >= 2) answer += st[i].len - st[st[i].link].len;
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s, s != "*") {
        SuffixAutomaton sam;
        for (char c : s) sam.extend(c);
        cout << sam.computeAnswer() << "\n";
    }
    return 0;
}
