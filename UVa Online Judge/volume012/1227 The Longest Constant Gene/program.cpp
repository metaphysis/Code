// The Longest Constant Gene
// UVa ID: 1227
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.900s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1000010;

// 后缀自动机结构体
struct SuffixAutomaton {
    // 状态节点结构体
    struct State {
        int len;        // 该状态能够接受的最长子串长度
        int link;       // 后缀链接，指向更短的后缀状态
        int next[4];    // 状态转移数组，4 个字符（A, C, G, T）
    };
    
    vector<State> st;   // 状态数组
    int sz;             // 当前状态数量
    int last;           // 最后一个状态
    
    // 构造函数，初始化后缀自动机
    SuffixAutomaton(int maxSize) {
        st.resize(maxSize * 2);  // 预留足够空间
        sz = last = 0;
        // 初始化初始状态（空串状态）
        st[0].len = 0;
        st[0].link = -1;
        memset(st[0].next, -1, sizeof(st[0].next));
        sz++;  // 状态计数加 1
    }
    
    // 扩展自动机，添加一个字符
    void extend(int c) {
        // 创建新状态
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        memset(st[cur].next, -1, sizeof(st[cur].next));
        
        // 从 last 状态开始，沿着后缀链接回溯
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;  // 添加转移
            p = st[p].link;       // 沿着后缀链接回溯
        }
        
        if (p == -1) {
            // 情况 1：回溯到初始状态，设置新状态的后缀链接为初始状态
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                // 情况 2：q 状态正好可以接受新字符
                st[cur].link = q;
            } else {
                // 情况 3：需要分裂状态
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
                st[clone].link = st[q].link;
                
                // 更新转移指向新分裂的状态
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;  // 更新最后一个状态
    }
    
    // 字符到整数的映射函数
    int charToInt(char ch) const {
        switch(ch) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
            default: return 0;
        }
    }
};

// 在后缀自动机上运行字符串 s，返回每个状态的最大匹配长度
vector<int> runString(const SuffixAutomaton& sa, const string& s) {
    int n = s.size();
    vector<int> matchLen(sa.sz, 0);  // 记录每个状态的最大匹配长度
    int v = 0;  // 当前状态
    int l = 0;  // 当前匹配长度
    
    // 遍历字符串的每个字符
    for (int i = 0; i < n; i++) {
        int c = sa.charToInt(s[i]);
        // 如果当前状态没有对应字符的转移，沿着后缀链接回溯
        while (v != 0 && sa.st[v].next[c] == -1) {
            v = sa.st[v].link;
            l = sa.st[v].len;
        }
        // 如果找到转移，更新状态和匹配长度
        if (sa.st[v].next[c] != -1) {
            v = sa.st[v].next[c];
            l++;
        }
        matchLen[v] = max(matchLen[v], l);  // 更新该状态的最大匹配长度
    }
    
    // 按状态长度排序，从长到短传递匹配长度
    vector<int> order(sa.sz);
    vector<int> cnt(sa.st[sa.last].len + 1, 0);
    
    // 计数排序：统计每个长度的状态数量
    for (int i = 0; i < sa.sz; i++) {
        cnt[sa.st[i].len]++;
    }
    for (int i = 1; i <= sa.st[sa.last].len; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < sa.sz; i++) {
        order[--cnt[sa.st[i].len]] = i;
    }
    
    // 从长到短传递匹配长度信息
    for (int i = sa.sz - 1; i >= 0; i--) {
        int v = order[i];
        if (sa.st[v].link != -1) {
            matchLen[sa.st[v].link] = max(matchLen[sa.st[v].link], matchLen[v]);
        }
    }
    
    return matchLen;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<string> genomes(N);
        
        // 读入所有基因组字符串
        for (int i = 0; i < N; i++) {
            cin >> genomes[i];
        }
        
        // 找到最短的字符串来构建自动机（减少状态数）
        int minIdx = 0;
        for (int i = 1; i < N; i++) {
            if (genomes[i].size() < genomes[minIdx].size()) {
                minIdx = i;
            }
        }
        
        // 将最短字符串换到第一个位置
        if (minIdx != 0) {
            swap(genomes[0], genomes[minIdx]);
        }
        
        // 对第一个字符串构建后缀自动机
        SuffixAutomaton sa(genomes[0].size());
        for (char c : genomes[0]) {
            sa.extend(sa.charToInt(c));
        }
        
        // 初始化全局最小匹配长度为第一个字符串的自动机状态长度
        vector<int> globalMin(sa.sz, sa.st[0].len);
        for (int i = 0; i < sa.sz; i++) {
            globalMin[i] = sa.st[i].len;
        }
        
        // 对每个其他字符串运行自动机，更新最小匹配长度
        for (int i = 1; i < N; i++) {
            vector<int> currentMatch = runString(sa, genomes[i]);
            for (int j = 0; j < sa.sz; j++) {
                globalMin[j] = min(globalMin[j], currentMatch[j]);
            }
        }
        
        // 找到最大的最小匹配长度
        int ans = 0;
        for (int i = 0; i < sa.sz; i++) {
            ans = max(ans, globalMin[i]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
