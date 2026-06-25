// Boring Homework
// UVa ID: 12010
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, left, right, depth, col;
    Node() : val(0), left(-1), right(-1), depth(0), col(-1) {}
};

void insertNode(vector<Node>& tree, int& root, int val, int depth) {
    if (root == -1) {
        root = val - 1;
        tree[root].val = val;
        tree[root].depth = depth;
        return;
    }
    if (val < tree[root].val) {
        if (tree[root].left == -1) {
            tree[root].left = val - 1;
            tree[val - 1].val = val;
            tree[val - 1].depth = depth + 1;
        } else insertNode(tree, tree[root].left, val, depth + 1);
    } else {
        if (tree[root].right == -1) {
            tree[root].right = val - 1;
            tree[val - 1].val = val;
            tree[val - 1].depth = depth + 1;
        } else insertNode(tree, tree[root].right, val, depth + 1);
    }
}

void inorderAssignCol(vector<Node>& tree, int cur, int& idx) {
    if (cur == -1) return;
    inorderAssignCol(tree, tree[cur].left, idx);
    tree[cur].col = idx++;
    inorderAssignCol(tree, tree[cur].right, idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        vector<int> seq(N);
        for (int i = 0; i < N; ++i) cin >> seq[i];

        vector<Node> tree(N);
        int root = -1;
        for (int i = 0; i < N; ++i) insertNode(tree, root, seq[i], 0);

        int maxDepth = 0;
        for (int i = 0; i < N; ++i) if (tree[i].depth > maxDepth) maxDepth = tree[i].depth;

        int colIdx = 0;
        inorderAssignCol(tree, root, colIdx);

        int rows = 2 * maxDepth + 1;
        int cols = N;
        vector<vector<char>> grid(rows, vector<char>(cols, ' '));

        // 放置节点 'o'
        for (int i = 0; i < N; ++i) {
            int r = 2 * tree[i].depth;
            int c = tree[i].col;
            grid[r][c] = 'o';
        }

        // 放置 '|' 和 '+'（非根节点）
        for (int i = 0; i < N; ++i) {
            if (tree[i].depth > 0) {
                int r = 2 * tree[i].depth;
                int c = tree[i].col;
                grid[r - 1][c] = '|';
                grid[r - 2][c] = '+';
            }
        }

        // 画横线 '-'（对有孩子的节点）
        for (int i = 0; i < N; ++i) {
            int lc = tree[i].left, rc = tree[i].right;
            if (lc == -1 && rc == -1) continue;
            int r = 2 * tree[i].depth;
            int leftCol = (lc != -1) ? tree[lc].col : tree[i].col;
            int rightCol = (rc != -1) ? tree[rc].col : tree[i].col;
            if (leftCol > rightCol) swap(leftCol, rightCol);
            for (int c = leftCol; c <= rightCol; ++c)
                if (grid[r][c] == ' ') grid[r][c] = '-';
        }

        // 输出图形，保留前导空格，去除尾部空格
        cout << "Case #" << caseNo << ":\n";
        for (int r = 0; r < rows; ++r) {
            int last = -1;
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] != ' ') last = c;
            if (last == -1) { cout << "\n"; continue; }
            for (int c = 0; c <= last; ++c) cout << grid[r][c];
            cout << "\n";
        }
    }
    return 0;
}
