#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long minVal, maxVal, incProfit, decProfit;
    bool empty;
    Info() : minVal(0), maxVal(0), incProfit(0), decProfit(0), empty(true) {}
    Info(long long value) : minVal(value), maxVal(value), incProfit(0), decProfit(0), empty(false) {}
};

Info mergeInfo(const Info &leftInfo, const Info &rightInfo) {
    if (leftInfo.empty) return rightInfo;
    if (rightInfo.empty) return leftInfo;
    Info result;
    result.empty = false;
    result.minVal = min(leftInfo.minVal, rightInfo.minVal);
    result.maxVal = max(leftInfo.maxVal, rightInfo.maxVal);
    result.incProfit = max(max(leftInfo.incProfit, rightInfo.incProfit), rightInfo.maxVal - leftInfo.minVal);
    result.decProfit = max(max(leftInfo.decProfit, rightInfo.decProfit), leftInfo.maxVal - rightInfo.minVal);
    return result;
}

Info reverseInfo(Info info) {
    if (info.empty) return info;
    swap(info.incProfit, info.decProfit);
    return info;
}

class SegmentTree {
public:
    SegmentTree(const vector<long long> &values, int size) : n(size), tree(size * 4 + 5), lazy(size * 4 + 5, 0) {
        buildTree(1, 1, n, values);
    }

    void add(int left, int right, long long value) {
        addRange(1, 1, n, left, right, value);
    }

    Info query(int left, int right) {
        return queryRange(1, 1, n, left, right);
    }

private:
    int n;
    vector<Info> tree;
    vector<long long> lazy;

    void applyNode(int node, long long value) {
        tree[node].minVal += value;
        tree[node].maxVal += value;
        lazy[node] += value;
    }

    void pushDown(int node) {
        if (lazy[node] == 0) return;
        applyNode(node * 2, lazy[node]);
        applyNode(node * 2 + 1, lazy[node]);
        lazy[node] = 0;
    }

    void buildTree(int node, int left, int right, const vector<long long> &values) {
        if (left == right) {
            tree[node] = Info(values[left]);
            return;
        }
        int mid = (left + right) / 2;
        buildTree(node * 2, left, mid, values);
        buildTree(node * 2 + 1, mid + 1, right, values);
        tree[node] = mergeInfo(tree[node * 2], tree[node * 2 + 1]);
    }

    void addRange(int node, int left, int right, int queryLeft, int queryRight, long long value) {
        if (queryLeft <= left && right <= queryRight) {
            applyNode(node, value);
            return;
        }
        pushDown(node);
        int mid = (left + right) / 2;
        if (queryLeft <= mid) addRange(node * 2, left, mid, queryLeft, queryRight, value);
        if (queryRight > mid) addRange(node * 2 + 1, mid + 1, right, queryLeft, queryRight, value);
        tree[node] = mergeInfo(tree[node * 2], tree[node * 2 + 1]);
    }

    Info queryRange(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryLeft <= left && right <= queryRight) return tree[node];
        pushDown(node);
        int mid = (left + right) / 2;
        if (queryRight <= mid) return queryRange(node * 2, left, mid, queryLeft, queryRight);
        if (queryLeft > mid) return queryRange(node * 2 + 1, mid + 1, right, queryLeft, queryRight);
        Info leftInfo, rightInfo;
        if (queryLeft <= mid) leftInfo = queryRange(node * 2, left, mid, queryLeft, queryRight);
        if (queryRight > mid) rightInfo = queryRange(node * 2 + 1, mid + 1, right, queryLeft, queryRight);
        return mergeInfo(leftInfo, rightInfo);
    }
};

void addPath(int startNode, int endNode, long long value, const vector<int> &parent, const vector<int> &depth, const vector<int> &top, const vector<int> &position, SegmentTree &segTree) {
    while (top[startNode] != top[endNode]) {
        if (depth[top[startNode]] < depth[top[endNode]]) swap(startNode, endNode);
        segTree.add(position[top[startNode]], position[startNode], value);
        startNode = parent[top[startNode]];
    }
    int leftPos = min(position[startNode], position[endNode]), rightPos = max(position[startNode], position[endNode]);
    segTree.add(leftPos, rightPos, value);
}

Info getPathInfo(int startNode, int endNode, const vector<int> &parent, const vector<int> &depth, const vector<int> &top, const vector<int> &position, SegmentTree &segTree) {
    Info leftInfo, rightInfo;
    while (top[startNode] != top[endNode]) {
        if (depth[top[startNode]] >= depth[top[endNode]]) {
            Info part = reverseInfo(segTree.query(position[top[startNode]], position[startNode]));
            leftInfo = mergeInfo(leftInfo, part);
            startNode = parent[top[startNode]];
        } else {
            Info part = segTree.query(position[top[endNode]], position[endNode]);
            rightInfo = mergeInfo(part, rightInfo);
            endNode = parent[top[endNode]];
        }
    }
    if (depth[startNode] >= depth[endNode]) {
        Info part = reverseInfo(segTree.query(position[endNode], position[startNode]));
        leftInfo = mergeInfo(leftInfo, part);
    } else {
        Info part = segTree.query(position[startNode], position[endNode]);
        leftInfo = mergeInfo(leftInfo, part);
    }
    return mergeInfo(leftInfo, rightInfo);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n) {
        vector<long long> price(n + 1);
        vector<vector<int>> graph(n + 1);
        for (int i = 1; i <= n; ++i) cin >> price[i];
        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        vector<int> parent(n + 1), depth(n + 1), subSize(n + 1), heavy(n + 1, -1), top(n + 1), position(n + 1), order, stackNodes;
        order.reserve(n);
        order.push_back(1);
        for (int i = 0; i < (int)order.size(); ++i) {
            int node = order[i];
            for (int next : graph[node]) {
                if (next == parent[node]) continue;
                parent[next] = node;
                depth[next] = depth[node] + 1;
                order.push_back(next);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            int node = order[i];
            subSize[node] = 1;
            for (int next : graph[node]) {
                if (next == parent[node]) continue;
                subSize[node] += subSize[next];
                if (heavy[node] == -1 || subSize[next] > subSize[heavy[node]]) heavy[node] = next;
            }
        }
        int currentPos = 1;
        stackNodes.push_back(1);
        while (!stackNodes.empty()) {
            int startNode = stackNodes.back();
            stackNodes.pop_back();
            int chainTop = startNode, node = startNode;
            while (node != -1) {
                top[node] = chainTop;
                position[node] = currentPos;
                ++currentPos;
                for (int next : graph[node]) if (next != parent[node] && next != heavy[node]) stackNodes.push_back(next);
                node = heavy[node];
            }
        }
        vector<long long> base(n + 1);
        for (int node = 1; node <= n; ++node) base[position[node]] = price[node];
        SegmentTree segTree(base, n);
        cin >> q;
        while (q--) {
            int startNode, endNode;
            long long value;
            cin >> startNode >> endNode >> value;
            addPath(startNode, endNode, value, parent, depth, top, position, segTree);
            cout << getPathInfo(startNode, endNode, parent, depth, top, position, segTree).incProfit << '\n';
        }
    }
    return 0;
}
