#include <bits/stdc++.h>
using namespace std;

const int MAXN = 120005;

struct Node {
    int rawId, prior, left, right, subSize;
    vector<int> cols;
} tree[MAXN];
int totNode, rootNode, rawCnt;
vector<pair<int, int>> shapes[7][4];
int getSize(int u) {
    return u ? tree[u].subSize : 0;
}

void updateSize(int u) {
    tree[u].subSize = getSize(tree[u].left) + getSize(tree[u].right) + 1;
}

int rnd() {
    static uint32_t seed = 123456789;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

int newRow(int rawId) {
    ++totNode;
    tree[totNode].rawId = rawId;
    tree[totNode].prior = rnd();
    tree[totNode].left = 0;
    tree[totNode].right = 0;
    tree[totNode].subSize = 1;
    tree[totNode].cols.clear();
    return totNode;
}

int mergeTreap(int a, int b) {
    if (!a || !b) return a ? a : b;
    if (tree[a].prior > tree[b].prior) {
        tree[a].right = mergeTreap(tree[a].right, b);
        updateSize(a);
        return a;
    } else {
        tree[b].left = mergeTreap(a, tree[b].left);
        updateSize(b);
        return b;
    }
}

void splitTreap(int u, int key, int &a, int &b) {
    if (!u) {
        a = b = 0;
        return;
    }
    if (tree[u].rawId < key) {
        a = u;
        splitTreap(tree[u].right, key, tree[u].right, b);
        updateSize(a);
    } else {
        b = u;
        splitTreap(tree[u].left, key, a, tree[u].left);
        updateSize(b);
    }
}

int getRank(int u, int key) {
    if (!u) return 0;
    if (key == tree[u].rawId) return getSize(tree[u].left);
    if (key < tree[u].rawId) return getRank(tree[u].left, key);
    return getSize(tree[u].left) + 1 + getRank(tree[u].right, key);
}

int kthNode(int u, int k) {
    int leftSize = getSize(tree[u].left);
    if (k < leftSize) return kthNode(tree[u].left, k);
    if (k == leftSize) return u;
    return kthNode(tree[u].right, k - leftSize - 1);
}

int getHeight(int colIdx, vector<set<int>> &colSet) {
    if (colSet[colIdx].empty()) return 0;
    int raw = *colSet[colIdx].rbegin();
    return getRank(rootNode, raw) + 1;
}

void initShapes() {
    vector<pair<int, int>> base[7];
    base[0] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    base[1] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}};
    base[2] = {{0, 0}, {1, 0}, {2, 0}, {2, 1}};
    base[3] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    base[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    base[5] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
    base[6] = {{1, 0}, {2, 0}, {0, 1}, {1, 1}};
    for (int typeIdx = 0; typeIdx < 7; ++typeIdx) {
        vector<pair<int, int>> cur = base[typeIdx];
        for (int angleIdx = 0; angleIdx < 4; ++angleIdx) {
            shapes[typeIdx][angleIdx] = cur;
            int width = 0, height = 0;
            for (auto &p : cur) {
                width = max(width, p.first + 1);
                height = max(height, p.second + 1);
            }
            vector<pair<int, int>> nxt;
            for (auto &p : cur) nxt.push_back({p.second, width - 1 - p.first});
            cur = nxt;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    initShapes();
    int testCount;
    cin >> testCount;
    for (int caseIdx = 1; caseIdx <= testCount; ++caseIdx) {
        int width, num;
        cin >> width >> num;
        vector<set<int>> colSet(width);
        totNode = 0;
        rootNode = 0;
        rawCnt = 0;
        long long totalScore = 0;
        for (int i = 0; i < num; ++i) {
            char typeChar;
            int leftCol, degree;
            cin >> typeChar >> leftCol >> degree;
            int typeIdx = 0;
            if (typeChar == 'I') typeIdx = 0;
            else if (typeChar == 'J') typeIdx = 1;
            else if (typeChar == 'L') typeIdx = 2;
            else if (typeChar == 'O') typeIdx = 3;
            else if (typeChar == 'S') typeIdx = 4;
            else if (typeChar == 'T') typeIdx = 5;
            else if (typeChar == 'Z') typeIdx = 6;
            int angleIdx = degree / 90;
            auto &cells = shapes[typeIdx][angleIdx];
            int base = 1;
            for (auto &cell : cells) {
                int colIdx = leftCol + cell.first;
                int h = getHeight(colIdx, colSet);
                base = max(base, h - cell.second + 1);
            }
            int maxR = 0;
            for (auto &cell : cells) maxR = max(maxR, base + cell.second);
            while (getSize(rootNode) < maxR) {
                int newRaw = ++rawCnt;
                int newNode = newRow(newRaw);
                rootNode = mergeTreap(rootNode, newNode);
            }
            vector<int> fullRows;
            for (auto &cell : cells) {
                int colIdx = leftCol + cell.first;
                int rowIdx = base + cell.second;
                int node = kthNode(rootNode, rowIdx - 1);
                tree[node].cols.push_back(colIdx);
                colSet[colIdx].insert(tree[node].rawId);
                if (tree[node].cols.size() == width) fullRows.push_back(node);
            }
            int cleared = fullRows.size();
            if (cleared == 1) totalScore += 100;
            else if (cleared == 2) totalScore += 250;
            else if (cleared == 3) totalScore += 400;
            else if (cleared == 4) totalScore += 1000;
            for (int node : fullRows) {
                int raw = tree[node].rawId;
                for (int colIdx : tree[node].cols) colSet[colIdx].erase(raw);
                int a, b, mid, cc;
                splitTreap(rootNode, raw, a, b);
                splitTreap(b, raw + 1, mid, cc);
                rootNode = mergeTreap(a, cc);
            }
        }
        cout << "Case #" << caseIdx << ":\n";
        cout << totalScore << "\n";
        for (int i = 0; i < width; ++i) {
            if (i) cout << ' ';
            cout << getHeight(i, colSet);
        }
        cout << "\n";
    }
    return 0;
}
