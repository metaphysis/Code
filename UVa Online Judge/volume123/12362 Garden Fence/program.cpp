#include <bits/stdc++.h>
using namespace std;

struct Tree {
    long long x, y;
    int v;
    bool pine;
};

struct Node {
    long long x, y, kx, ky;
    int v;
    bool pine;
};

bool cmpNode(const Node &a, const Node &b) {
    return a.kx * b.ky - a.ky * b.kx > 0;
}

bool sameDir(const Node &a, const Node &b) {
    return a.kx * b.ky == a.ky * b.kx;
}

long long addA(const Node &node, bool left) {
    return node.pine == left ? node.v : 0;
}

long long addB(const Node &node, bool left) {
    return node.pine != left ? node.v : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, l;
    while (cin >> p >> l && (p || l)) {
        int n = p + l;
        long long total = 0, bestKeep = 0;
        vector<Tree> trees(n);
        for (int i = 0; i < n; i++) {
            cin >> trees[i].x >> trees[i].y >> trees[i].v;
            trees[i].pine = i < p;
            total += trees[i].v;
        }
        for (int root = 0; root < n; root++) {
            long long keepA = 0, keepB = 0;
            vector<Node> nodes;
            nodes.reserve(n - 1);
            for (int i = 0; i < n; i++) {
                if (i == root) continue;
                long long x = trees[i].x - trees[root].x, y = trees[i].y - trees[root].y;
                long long kx = x, ky = y;
                if (ky < 0 || (ky == 0 && kx < 0)) {
                    kx = -kx;
                    ky = -ky;
                }
                Node node = {x, y, kx, ky, trees[i].v, trees[i].pine};
                bool left = y > 0 || (y == 0 && x > 0);
                keepA += addA(node, left);
                keepB += addB(node, left);
                nodes.push_back(node);
            }
            sort(nodes.begin(), nodes.end(), cmpNode);
            bestKeep = max(bestKeep, keepA + (trees[root].pine ? trees[root].v : 0));
            bestKeep = max(bestKeep, keepB + (!trees[root].pine ? trees[root].v : 0));
            for (int i = 0; i < (int)nodes.size();) {
                int j = i;
                while (j < (int)nodes.size() && sameDir(nodes[i], nodes[j])) j++;
                for (int k = i; k < j; k++) {
                    long long dot = nodes[i].kx * nodes[k].x + nodes[i].ky * nodes[k].y;
                    bool left = dot > 0;
                    keepA += addA(nodes[k], !left) - addA(nodes[k], left);
                    keepB += addB(nodes[k], !left) - addB(nodes[k], left);
                }
                bestKeep = max(bestKeep, keepA + (trees[root].pine ? trees[root].v : 0));
                bestKeep = max(bestKeep, keepB + (!trees[root].pine ? trees[root].v : 0));
                i = j;
            }
        }
        cout << total - bestKeep << '\n';
    }
    return 0;
}
