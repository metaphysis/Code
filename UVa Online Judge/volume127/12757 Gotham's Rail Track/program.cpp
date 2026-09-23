#include <bits/stdc++.h>
using namespace std;

struct Node {
    int left, right, parent, size;
    unsigned priority;
    bool reversed, cycle;
    Node() : left(0), right(0), parent(0), size(0), priority(0), reversed(false), cycle(false) {}
};

struct RailTrack {
    vector<Node> nodes;
    vector<int> path;
    mt19937 rng;
    RailTrack(int n) : nodes(n + 1), rng(chrono::steady_clock::now().time_since_epoch().count()) {
        path.reserve(n);
        for (int i = 1; i <= n; ++i) {
            nodes[i].size = 1;
            nodes[i].priority = rng();
        }
    }

    void pull(int root) {
        int left = nodes[root].left, right = nodes[root].right;
        nodes[root].size = nodes[left].size + nodes[right].size + 1;
        if (left) nodes[left].parent = root;
        if (right) nodes[right].parent = root;
    }

    void reverseTree(int root) {
        if (!root) return;
        swap(nodes[root].left, nodes[root].right);
        nodes[root].reversed = !nodes[root].reversed;
    }

    void push(int root) {
        if (!nodes[root].reversed) return;
        reverseTree(nodes[root].left);
        reverseTree(nodes[root].right);
        nodes[root].reversed = false;
    }

    int mergeTrees(int leftRoot, int rightRoot) {
        if (!leftRoot || !rightRoot) {
            int root = leftRoot ? leftRoot : rightRoot;
            if (root) nodes[root].parent = 0;
            return root;
        }
        if (nodes[leftRoot].priority > nodes[rightRoot].priority) {
            push(leftRoot);
            nodes[leftRoot].right = mergeTrees(nodes[leftRoot].right, rightRoot);
            pull(leftRoot);
            nodes[leftRoot].parent = 0;
            return leftRoot;
        } else {
            push(rightRoot);
            nodes[rightRoot].left = mergeTrees(leftRoot, nodes[rightRoot].left);
            pull(rightRoot);
            nodes[rightRoot].parent = 0;
            return rightRoot;
        }
    }

    void splitTree(int root, int count, int &leftRoot, int &rightRoot) {
        if (!root) {
            leftRoot = rightRoot = 0;
            return;
        }
        push(root);
        int leftSize = nodes[nodes[root].left].size;
        if (count <= leftSize) {
            rightRoot = root;
            splitTree(nodes[root].left, count, leftRoot, nodes[root].left);
            pull(rightRoot);
            nodes[rightRoot].parent = 0;
        } else {
            leftRoot = root;
            splitTree(nodes[root].right, count - leftSize - 1, nodes[root].right, rightRoot);
            pull(leftRoot);
            nodes[leftRoot].parent = 0;
        }
    }

    pair<int, int> getInfo(int node) {
        path.clear();
        int current = node, position;
        while (current) {
            path.push_back(current);
            current = nodes[current].parent;
        }
        for (int i = (int)path.size() - 1; i >= 0; --i) push(path[i]);
        position = nodes[nodes[node].left].size + 1;
        current = node;
        while (nodes[current].parent) {
            int parent = nodes[current].parent;
            if (nodes[parent].right == current) position += nodes[nodes[parent].left].size + 1;
            current = parent;
        }
        return {current, position};
    }

    void linkBlocks(int u, int v) {
        pair<int, int> uInfo = getInfo(u), vInfo = getInfo(v);
        int uRoot = uInfo.first, vRoot = vInfo.first;
        if (uRoot == vRoot) {
            nodes[uRoot].cycle = true;
            return;
        }
        if (uInfo.second == 1) reverseTree(uRoot);
        if (vInfo.second == nodes[vRoot].size) reverseTree(vRoot);
        mergeTrees(uRoot, vRoot);
    }

    void cutBlocks(int u, int v) {
        pair<int, int> uInfo = getInfo(u), vInfo = getInfo(v);
        int root = uInfo.first, uPos = uInfo.second, vPos = vInfo.second, leftRoot, rightRoot;
        if (uPos > vPos) swap(uPos, vPos);
        if (!nodes[root].cycle) {
            splitTree(root, uPos, leftRoot, rightRoot);
            return;
        }
        nodes[root].cycle = false;
        if (uPos == 1 && vPos == nodes[root].size) return;
        splitTree(root, uPos, leftRoot, rightRoot);
        mergeTrees(rightRoot, leftRoot);
    }

    int queryDistance(int u, int v) {
        if (u == v) return 1;
        pair<int, int> uInfo = getInfo(u), vInfo = getInfo(v);
        int root = uInfo.first, distance = abs(uInfo.second - vInfo.second);
        if (root != vInfo.first) return -1;
        if (nodes[root].cycle) return max(distance, nodes[root].size - distance) + 1;
        return distance + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int n, q;
        cin >> n >> q;
        RailTrack track(n);
        cout << "Case " << caseId << ":\n";
        for (int i = 0; i < q; ++i) {
            int type, u, v;
            cin >> type >> u >> v;
            if (type == 1) track.linkBlocks(u, v);
            else if (type == 2) track.cutBlocks(u, v);
            else cout << track.queryDistance(u, v) << '\n';
        }
    }
    return 0;
}
