// BUT We Need a Diagram
// UVa ID: 692
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

#define FOR(i, e) for (int i = 0; i < e; i++)
#define FORB(i, s, e) for (int i = s; i < e; i++)
#define FORBE(i, s, e) for (int i = s; i <= e; i++)

struct Node {
    char label;
    int type;
    Node *left, *right;
    Node(char g, int t = 0) : label(g), type(t), left(0), right(0) {}
};

Node* parse(const string& s, int& idx) {
    char label = s[idx++];
    if (idx < s.size() && s[idx] == '(') {
        idx++;
        Node* left = parse(s, idx);
        if (idx < s.size() && s[idx] == ',') {
            idx++;
            Node* right = parse(s, idx);
            idx++;
            Node* node = new Node(label, 2);
            node->left = left;
            node->right = right;
            return node;
        } else {
            idx++;
            Node* node = new Node(label, 1);
            node->left = left;
            return node;
        }
    }
    return new Node(label, 0);
}

using Grid = vector<vector<char>>;
using Row = vector<char>;

void cut(Grid& g) {
    while (1) {
        int ok = 1;
        FOR (i, g.size())
            if (g[i].front() != ' ')
                ok = 0;
        if (ok) {
            FOR (i, g.size())
                g[i].erase(g[i].begin());
        } else break;
    }
    while (1) {
        int ok = 1;
        FOR (i, g.size())
            if (g[i].back() != ' ')
                ok = 0;
        if (ok) {
            FOR (i, g.size())
                g[i].pop_back();
        } else break;
    }
}

Grid merge(Grid g1, Grid g2) {
    Grid g;
    int rows = max(g1.size(), g2.size());
    while (g1.size() < rows) g1.insert(g1.begin(), Row(g1.back().size(), ' '));
    while (g2.size() < rows) g2.insert(g2.begin(), Row(g2.back().size(), ' '));
    // 关键：给左子图右侧添加一个空格列，确保初始间距至少为1
    FOR (i, rows) g1[i].push_back(' ');
    int s = max(g1[0].size(), g2[0].size());
    while (g1[0].size() < s) FOR (i, rows) g1[i].insert(g1[i].begin(), ' ');
    while (g2[0].size() < s) FOR (i, rows) g2[i].push_back(' ');
    // 计算每行左右最近非空字符之间的列差（即中间空格数），取最小值 d
    int d = INT_MAX;
    FOR (i, rows) {
        int j = s - 1, c = 0;
        while (g1[i][j] == ' ') j--, c++;
        j = 0;
        while (g2[i][j] == ' ') j++, c++;
        d = min(d, c);
    }
    // 尝试向左重叠，最大可重叠量为 d-1（因为至少要留一列空格）
    int md = 0;
    while (md <= d - 1) {
        int ok = 1;
        // 检查叶子正上方无减号（重叠区域）
        for (int i = 1; i < rows; i++) {
            for (int j = 0, k = md; j < md; j++, k--)
                if (g1[i][s - j - 1] != ' ' && g1[i - 1][s - j - 1] == ' ' && g2[i - 1][k - 1] == '-')
                    ok = 0;
            for (int j = 0, k = md; j < md; j++, k--) {
                if (g2[i][j] != ' ' && g2[i - 1][j] == ' ' && g1[i - 1][s - k] == '-')
                    ok = 0;
            }
        }
        if (!ok) break;
        md++;
    }
    md--;
    // 按最终重叠量 md 合并
    FOR (i, rows) {
        Row r(g1[i]);
        FOR (j, s) r.push_back(' ');
        FOR (j, s) if (g2[i][j] != ' ') r[s - md + j] = g2[i][j];
        g.push_back(r);
    }
    cut(g);
    return g;
}
    
Grid dfs(Node *root) {
    Grid g;
    if (root->type == 0) g.push_back(Row(1, root->label));
    else if (root->type == 1) {
        g = dfs(root->left);
        int c = -1;
        FOR (i, g.back().size())
            if (g.back()[i] != ' ') {
                c = i;
                break;
            }
        Row r(g.back().size(), ' '); r[c] = '-'; g.push_back(r);
        r[c] = root->label; g.push_back(r);
        return g;
    } else {
        g = merge(dfs(root->left), dfs(root->right));
        Row last = g.back();
        int fc = -1, rc = -1, n = last.size();
        FOR (i, n)
            if (last[i] != ' ') {
                fc = i;
                break;
            }
        FORB (i, fc + 1, n)
            if (last[i] != ' ') {
                rc = i;
                break;
            }
        Row r1(n, ' ');
        FORBE (i, fc, rc) r1[i] = '-'; g.push_back(r1);
        Row r2(n, ' '); r2[(fc + rc) / 2] = root->label; g.push_back(r2);
    }
    return g;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    char c; string tree; int id = 1;
    while (cin >> c) {
        if (c == ';' || c == '.') {
            cout << id++ << ":\n";
            int idx = 0;
            Grid G = dfs(parse(tree, idx));
            for (auto r : G) {
                int end = r.size() - 1;
                while (r[end] == ' ') end--;
                FORBE (i, 0, end) cout << r[i];
                cout << '\n';
            }
            tree.clear();
        } else tree += c;
        if (c == '.') break;
    }
    return 0;
}
