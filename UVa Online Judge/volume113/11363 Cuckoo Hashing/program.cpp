// Cuckoo Hashing
// UVa ID: 11363
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int m, n;
int h1[MAXN], h2[MAXN];
int table[MAXN];
bool visited[MAXN];

bool dfs(int word) {
    if (visited[word]) return false;
    visited[word] = true;
    
    int pos1 = h1[word], pos2 = h2[word];
    
    // 尝试第一个位置
    if (table[pos1] == -1) {
        table[pos1] = word;
        return true;
    }
    // 尝试第二个位置（若与第一个不同）
    if (pos1 != pos2 && table[pos2] == -1) {
        table[pos2] = word;
        return true;
    }
    
    // 方案一：驱逐第一个位置的单词
    int kicked1 = table[pos1];
    table[pos1] = word;
    if (dfs(kicked1)) return true;
    table[pos1] = kicked1;  // 回溯
    
    // 方案二：驱逐第二个位置的单词（若与第一个不同）
    if (pos1 != pos2) {
        int kicked2 = table[pos2];
        table[pos2] = word;
        if (dfs(kicked2)) return true;
        table[pos2] = kicked2;  // 回溯
    }
    
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &m, &n);
        for (int i = 0; i < m; ++i) 
            scanf("%d %d", &h1[i], &h2[i]);
        
        for (int i = 0; i < n; ++i) table[i] = -1;
        
        bool success = true;
        for (int i = 0; i < m; ++i) {
            memset(visited, 0, sizeof(bool) * m);
            if (!dfs(i)) {
                success = false;
                break;
            }
        }
        
        if (success) printf("successful hashing\n");
        else printf("rehash necessary\n");
    }
    return 0;
}
