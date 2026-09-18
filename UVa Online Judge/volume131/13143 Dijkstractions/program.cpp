#include <bits/stdc++.h>
using namespace std;

const long double logCap = 100.0L;
const long double valueCap = 1e100L;
const long double eps = 1e-12L;

struct Tower {
    int base, expId;
    long double logBase, logLogBase, value;
};

struct TreeNode {
    Tower tower;
    int left, right, parent, size;
    unsigned int priority;
    long double gap, sum;
};

struct Edge {
    int to, weight;
};

struct TowerSet {
    vector<TreeNode> tree;
    mt19937 rng;
    int root;
    TowerSet(int capacity) : rng(712367821), root(0) {
        tree.reserve(capacity + 2);
        tree.push_back(TreeNode());
        Tower one = {1, 0, 0.0L, 0.0L, 1.0L};
        root = addNode(one, 0.0L);
    }

    int getSize(int id) {
        return id ? tree[id].size : 0;
    }

    long double getSum(int id) {
        return id ? tree[id].sum : 0.0L;
    }

    void pull(int id) {
        tree[id].size = getSize(tree[id].left) + getSize(tree[id].right) + 1;
        tree[id].sum = min(logCap, getSum(tree[id].left) + tree[id].gap + getSum(tree[id].right));
    }

    int addNode(const Tower &tower, long double gap) {
        TreeNode node;
        node.tower = tower;
        node.left = node.right = node.parent = 0;
        node.size = 1;
        node.priority = rng();
        node.gap = node.sum = gap;
        tree.push_back(node);
        return (int)tree.size() - 1;
    }

    int mergeTree(int leftId, int rightId) {
        if (!leftId || !rightId) {
            int id = leftId ? leftId : rightId;
            if (id) tree[id].parent = 0;
            return id;
        }
        if (tree[leftId].priority < tree[rightId].priority) {
            int child = mergeTree(tree[leftId].right, rightId);
            tree[leftId].right = child;
            tree[child].parent = leftId;
            tree[leftId].parent = 0;
            pull(leftId);
            return leftId;
        } else {
            int child = mergeTree(leftId, tree[rightId].left);
            tree[rightId].left = child;
            tree[child].parent = rightId;
            tree[rightId].parent = 0;
            pull(rightId);
            return rightId;
        }
    }

    void splitTree(int id, int count, int &leftId, int &rightId) {
        if (!id) {
            leftId = rightId = 0;
            return;
        }
        int leftSize = getSize(tree[id].left), child = 0;
        if (count <= leftSize) {
            rightId = id;
            splitTree(tree[id].left, count, leftId, child);
            tree[id].left = child;
            if (child) tree[child].parent = id;
            tree[id].parent = 0;
            pull(id);
        } else {
            leftId = id;
            splitTree(tree[id].right, count - leftSize - 1, child, rightId);
            tree[id].right = child;
            if (child) tree[child].parent = id;
            tree[id].parent = 0;
            pull(id);
        }
    }

    int getRank(int id) {
        int rank = getSize(tree[id].left) + 1;
        while (tree[id].parent) {
            int parent = tree[id].parent;
            if (tree[parent].right == id) rank += getSize(tree[parent].left) + 1;
            id = parent;
        }
        return rank;
    }

    long double rangeSum(int id, int leftPos, int rightPos) {
        if (!id || leftPos > rightPos) return 0.0L;
        if (leftPos == 1 && rightPos == tree[id].size) return tree[id].sum;
        int mid = getSize(tree[id].left) + 1;
        long double result = 0.0L;
        if (leftPos < mid) result += rangeSum(tree[id].left, leftPos, min(rightPos, mid - 1));
        if (leftPos <= mid && mid <= rightPos) result += tree[id].gap;
        if (rightPos > mid) result += rangeSum(tree[id].right, max(1, leftPos - mid), rightPos - mid);
        return min(logCap, result);
    }

    long double getLogRatio(int firstId, int secondId) {
        if (firstId == secondId) return 0.0L;
        int firstRank = getRank(firstId), secondRank = getRank(secondId);
        if (firstRank > secondRank) return rangeSum(root, secondRank + 1, firstRank);
        return -rangeSum(root, firstRank + 1, secondRank);
    }

    Tower makeTower(int base, int expId) {
        Tower result;
        result.base = base;
        result.expId = expId;
        result.logBase = result.logLogBase = 0.0L;
        result.value = 1.0L;
        if (base == 1) return result;
        result.logBase = logl((long double)base);
        result.logLogBase = logl(result.logBase);
        long double expValue = tree[expId].tower.value, limit = logl(valueCap);
        if (expValue >= limit / result.logBase) result.value = valueCap;
        else result.value = expl(expValue * result.logBase);
        return result;
    }

    long double compareTower(const Tower &first, const Tower &second) {
        if (first.base == 1 && second.base == 1) return 0.0L;
        if (first.base == 1) return -min(logCap, second.logBase * tree[second.expId].tower.value);
        if (second.base == 1) return min(logCap, first.logBase * tree[first.expId].tower.value);
        long double diff = getLogRatio(first.expId, second.expId);
        long double z = diff + first.logLogBase - second.logLogBase;
        if (fabsl(z) <= eps) return 0.0L;
        if (z > 0.0L) {
            long double result = tree[first.expId].tower.value * first.logBase * (-expm1l(-z));
            return min(logCap, result);
        } else {
            long double result = tree[second.expId].tower.value * second.logBase * (-expm1l(z));
            return -min(logCap, result);
        }
    }

    void changeGap(int id, long double gap) {
        tree[id].gap = gap;
        while (id) {
            pull(id);
            id = tree[id].parent;
        }
    }

    int insertTower(const Tower &tower) {
        int current = root, count = 0, prevId = 0, nextId = 0;
        while (current) {
            long double diff = compareTower(tower, tree[current].tower);
            if (diff == 0.0L) return current;
            if (diff < 0.0L) {
                nextId = current;
                current = tree[current].left;
            } else {
                count += getSize(tree[current].left) + 1;
                prevId = current;
                current = tree[current].right;
            }
        }
        long double prevGap = prevId ? compareTower(tower, tree[prevId].tower) : 0.0L;
        long double nextGap = nextId ? compareTower(tree[nextId].tower, tower) : 0.0L;
        int newId = addNode(tower, prevGap), leftId = 0, rightId = 0;
        if (nextId) changeGap(nextId, nextGap);
        splitTree(root, count, leftId, rightId);
        root = mergeTree(mergeTree(leftId, newId), rightId);
        return newId;
    }
};

void solve() {
    int nodeCount, edgeCount, start, finish;
    cin >> nodeCount >> edgeCount >> start >> finish;
    vector<vector<Edge>> graph(nodeCount + 1);
    vector<int> inDegree(nodeCount + 1, 0), order;
    vector<int> valueId(nodeCount + 1, 0), bestNext(nodeCount + 1, 0);
    vector<int> minNext(nodeCount + 1, 0), bestBase(nodeCount + 1, 0);
    for (int i = 0; i < edgeCount; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
        ++inDegree[to];
    }
    queue<int> que;
    for (int u = 1; u <= nodeCount; ++u) if (inDegree[u] == 0) que.push(u);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        order.push_back(u);
        for (const Edge &edge : graph[u]) if (--inDegree[edge.to] == 0) que.push(edge.to);
    }
    TowerSet towerSet(nodeCount + 1);
    valueId[finish] = 1;
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        if (u == finish) continue;
        bool found = false;
        Tower bestTower = {1, 0, 0.0L, 0.0L, 1.0L};
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            if (!valueId[v]) continue;
            if (!minNext[u] || v < minNext[u]) minNext[u] = v;
            Tower candidate = towerSet.makeTower(edge.weight, valueId[v]);
            long double diff = found ? towerSet.compareTower(candidate, bestTower) : 1.0L;
            if (!found || diff > 0.0L || (diff == 0.0L && v < bestNext[u])) {
                found = true;
                bestTower = candidate;
                bestNext[u] = v;
                bestBase[u] = edge.weight;
            }
        }
        if (found) valueId[u] = towerSet.insertTower(bestTower);
    }
    if (!valueId[start]) {
        cout << '\n';
        return;
    }
    int current = start;
    bool lexMode = false, first = true;
    while (true) {
        if (!first) cout << ' ';
        cout << current;
        first = false;
        if (current == finish) break;
        if (!lexMode && bestBase[current] == 1) lexMode = true;
        current = lexMode ? minNext[current] : bestNext[current];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) solve();
    return 0;
}
