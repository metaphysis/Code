// Anti-Rhyme Pairs
// UVa ID: 12338
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.160s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 100005;
const int MAXL = 10005;
const int MAX_NODES = 1000005; // 因为 N * L <= 1e6

struct TrieNode {
    int depth;
    int parent;
    int children[26];
    TrieNode() : depth(0), parent(-1) {
        memset(children, -1, sizeof(children));
    }
};

vector<TrieNode> trie;
int wordEnd[MAXN]; // 记录每个单词在 Trie 中的结束节点

int addNode(int parent) {
    int idx = trie.size();
    trie.emplace_back();
    trie[idx].parent = parent;
    trie[idx].depth = (parent == -1) ? 0 : trie[parent].depth + 1;
    return idx;
}

void insert(const string& s, int wordIndex) {
    int node = 0; // root
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[node].children[c] == -1) {
            int newNode = addNode(node);
            trie[node].children[c] = newNode;
        }
        node = trie[node].children[c];
    }
    wordEnd[wordIndex] = node;
}

// LCA 相关
vector<int> euler;
int firstOccurrence[MAX_NODES];
int depth[MAX_NODES];
int eulerIndex;

void dfs(int u) {
    firstOccurrence[u] = eulerIndex;
    euler.push_back(u);
    eulerIndex++;
    for (int i = 0; i < 26; i++) {
        int v = trie[u].children[i];
        if (v != -1) {
            depth[v] = depth[u] + 1;
            dfs(v);
            euler.push_back(u);
            eulerIndex++;
        }
    }
}

vector<vector<int>> st;
vector<int> logTable;

void buildRMQ() {
    int n = euler.size();
    logTable.resize(n + 1);
    logTable[1] = 0;
    for (int i = 2; i <= n; i++) {
        logTable[i] = logTable[i / 2] + 1;
    }
    int k = logTable[n] + 1;
    st.assign(n, vector<int>(k));
    for (int i = 0; i < n; i++) {
        st[i][0] = euler[i];
    }
    for (int j = 1; j < k; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            int left = st[i][j - 1];
            int right = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (depth[left] < depth[right]) ? left : right;
        }
    }
}

int queryLCA(int u, int v) {
    int l = firstOccurrence[u];
    int r = firstOccurrence[v];
    if (l > r) swap(l, r);
    int j = logTable[r - l + 1];
    int leftNode = st[l][j];
    int rightNode = st[r - (1 << j) + 1][j];
    return (depth[leftNode] < depth[rightNode]) ? leftNode : rightNode;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int n;
        cin >> n;
        trie.clear();
        addNode(-1); // root

        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            insert(s, i);
        }

        // 准备 LCA
        euler.clear();
        eulerIndex = 0;
        depth[0] = 0;
        dfs(0);
        buildRMQ();

        int q;
        cin >> q;
        cout << "Case " << caseNum << ":\n";
        while (q--) {
            int i, j;
            cin >> i >> j;
            i--; j--;
            int u = wordEnd[i];
            int v = wordEnd[j];
            int lca = queryLCA(u, v);
            cout << trie[lca].depth << "\n";
        }
    }

    return 0;
}
