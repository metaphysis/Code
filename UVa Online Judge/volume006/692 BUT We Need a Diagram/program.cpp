// BUT We Need a Diagram
// UVa ID: 692
// Verdict: Accepted
// Submission Date: 2026-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

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
        int space = 1;
        for (int i = 0; i < g.size(); i++)
            if (g[i].front() != ' ')
                space = 0;
        if (space) {
            for (int i = 0; i < g.size(); i++)
                g[i].erase(g[i].begin());
        } else break;
    }
    while (1) {
        int space = 1;
        for (int i = 0; i < g.size(); i++)
            if (g[i].back() != ' ')
                space = 0;
        if (space) {
            for (int i = 0; i < g.size(); i++)
                g[i].pop_back();
        } else break;
    }
}

Grid merge(Grid g1, Grid g2) {
    Grid g;
    int rows = max(g1.size(), g2.size());
    while (g1.size() < rows) g1.insert(g1.begin(), Row(g1.back().size(), ' '));
    while (g2.size() < rows) g2.insert(g2.begin(), Row(g2.back().size(), ' '));
    int near = 0;
    for (int i = 0; i < rows; i++)
        if (g1[i].back() != ' ' && g2[i].front() != ' ') {
            near = 1;
            break;
        }
    if (near) {
        for (int i = 0; i < rows; i++) {
            Row r;
            for (auto c : g1[i]) r.push_back(c);
            r.push_back(' ');
            for (auto c : g2[i]) r.push_back(c);
            g.push_back(r);
        }
    } else {
        int d = 0;
        int width1 = g1[0].size(), width2 = g2[0].size();
        while (g1[0].size() < width2) {
            for (int i = 0; i < rows; i++)
                g1[i].insert(g1[i].begin(), ' ');
        }
        while (g2[0].size() < width1) {
            for (int i = 0; i < rows; i++)
                g2[i].push_back(' ');
        }
        width1 = g1[0].size(), width2 = g2[0].size();
        while (true) {
            int nd = d + 1;
            bool ok = true;
            for (int i = 0; i < rows; i++) {
                if (width1 - nd - 1 < 0 && nd >= width2) break;
                if (width1 - nd - 1 >= 0 && g1[i][width1 - nd - 1] != ' ' && g2[i].front() != ' ') {
                    ok = false;
                    break;
                }
                if (g1[i].back() != ' ' && nd < width2 && g2[i][nd] != ' ') {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
            for (int i = 1; i < rows && ok; i++) {
                for (int j = 0, k = nd; j < nd && ok; j++, k--)
                    if (g1[i][width1 - j - 1] != ' ' && g1[i - 1][width1 - j - 1] == ' ' && g2[i - 1][k - 1] == '-')
                        ok = false;
                for (int j = 0, k = nd; j < nd && ok; j++, k--) {
                    if (g2[i][j] != ' ' && g2[i - 1][j] == ' ' && g1[i - 1][width1 - k] == '-')
                        ok = false;
                }
            }
            if (!ok) break;
            d++;
        }
        for (int i = 0; i < rows; i++) {
            Row r;
            for (int j = 0; j < width1; j++) r.push_back(g1[i][j]);
            for (int j = 0; j < width2; j++) r.push_back(' ');
            for (int j = 0; j < width2; j++)
                if (g2[i][j] != ' ')
                    r[width1 - d + j] = g2[i][j];
            g.push_back(r);
        }
        cut(g);
    }
    return g;
}
    
Grid dfs(Node *root) {
    Grid g;
    if (root->type == 0) {
        g.push_back(Row(1, root->label));
        return g;
    }
    if (root->type == 1) {
        g = dfs(root->left);
        int c = -1;
        for (int i = 0; i < g.back().size(); i++)
            if (g.back()[i] != ' ') {
                c = i;
                break;
            }
        Row r(g.back().size(), ' '); r[c] = '-'; g.push_back(r);
        r[c] = root->label; g.push_back(r);
        return g;
    }
    g = merge(dfs(root->left), dfs(root->right));
    Row last = g.back();
    int fc = -1, rc = -1, n = last.size();
    for (int i = 0; i < n; i++)
        if (last[i] != ' ') {
            fc = i;
            break;
        }
    for (int i = fc + 1; i < n; i++)
        if (last[i] != ' ') {
            rc = i;
            break;
        }
    Row r1(n, ' ');
    for (int i = fc; i <= rc; i++) r1[i] = '-'; g.push_back(r1);
    Row r2(n, ' '); r2[(fc + rc) / 2] = root->label; g.push_back(r2);
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
                for (int i = 0; i <= end; i++) cout << r[i];
                cout << '\n';
            }
            tree.clear();
        } else tree += c;
        if (c == '.') break;
    }
    return 0;
}
