// 1127
// UVa ID: Word Puzzles
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.300s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <tuple>
using namespace std;

const int MAXN = 1000;
const int ALPHABET = 26;

// 8个方向：北、东北、东、东南、南、西南、西、西北
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
char dirChar[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

// Trie树节点结构
struct TrieNode {
    int wordIndex; // -1表示不是单词结尾，否则存储单词在words中的下标
    TrieNode* children[ALPHABET];
    TrieNode() : wordIndex(-1) {
        memset(children, 0, sizeof(children));
    }
};

// 向Trie树中插入单词
void insertWord(TrieNode* root, const string& word, int index) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'A';
        if (!node->children[idx]) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }
    node->wordIndex = index;
}

void solve() {
    int L, C, W;
    cin >> L >> C >> W;
    
    vector<string> grid(L);
    for (int i = 0; i < L; i++) {
        cin >> grid[i];
    }
    
    vector<string> words(W);
    for (int i = 0; i < W; i++) {
        cin >> words[i];
    }
    
    // 构建Trie树
    TrieNode* root = new TrieNode();
    for (int i = 0; i < W; i++) {
        insertWord(root, words[i], i);
    }
    
    // 存储每个单词的答案，初始化为未找到状态
    vector<tuple<int, int, char>> ans(W);
    for (int i = 0; i < W; i++) {
        ans[i] = make_tuple(-1, -1, ' ');
    }
    
    int foundCount = 0; // 已找到的单词数量，用于提前终止
    
    // 从每个位置每个方向在Trie树上搜索
    for (int r = 0; r < L && foundCount < W; r++) {
        for (int c = 0; c < C && foundCount < W; c++) {
            for (int dir = 0; dir < 8 && foundCount < W; dir++) {
                TrieNode* node = root;
                int nr = r, nc = c;
                // 沿着当前方向在Trie树上行走
                while (nr >= 0 && nr < L && nc >= 0 && nc < C && node) {
                    char ch = grid[nr][nc];
                    int idx = ch - 'A';
                    node = node->children[idx];
                    if (!node) break; // Trie树上无此分支，提前结束
                    
                    // 如果找到一个单词
                    if (node->wordIndex != -1) {
                        int wi = node->wordIndex;
                        if (get<0>(ans[wi]) == -1) { // 只记录第一次出现
                            ans[wi] = make_tuple(r, c, dirChar[dir]);
                            foundCount++;
                        }
                    }
                    
                    nr += dr[dir];
                    nc += dc[dir];
                }
            }
        }
    }
    
    // 输出结果
    for (int i = 0; i < W; i++) {
        cout << get<0>(ans[i]) << " " << get<1>(ans[i]) << " " << get<2>(ans[i]) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        if (i > 0) cout << endl;
        solve();
    }
    
    return 0;
}
