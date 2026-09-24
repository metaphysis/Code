#include <bits/stdc++.h>
using namespace std;

struct ExprNode {
    int type, value, left, right;
};

struct Constructor {
    int arity, root;
    vector<ExprNode> nodes;
};

struct SegTree {
    int limit;
    vector<int> tree;
    void init(int upper) {
        limit = upper;
        tree.assign((upper + 1) * 4 + 8, 0);
    }

    void add(int node, int left, int right, int pos) {
        if (left == right) {
            tree[node] = 1;
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid) add(node * 2, left, mid, pos);
        else add(node * 2 + 1, mid + 1, right, pos);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void add(int pos) {
        add(1, 0, limit, pos);
    }

    int count(int node, int left, int right, int ql, int qr) const {
        if (qr < left || right < ql || tree[node] == 0) return 0;
        if (ql <= left && right <= qr) return tree[node];
        int mid = (left + right) / 2;
        return count(node * 2, left, mid, ql, qr) + count(node * 2 + 1, mid + 1, right, ql, qr);
    }

    int count(int left, int right) const {
        return count(1, 0, limit, left, right);
    }

    int first(int node, int left, int right, int ql, int qr) const {
        if (qr < left || right < ql || tree[node] == 0) return -1;
        if (left == right) return left;
        int mid = (left + right) / 2;
        int pos = first(node * 2, left, mid, ql, qr);
        if (pos != -1) return pos;
        return first(node * 2 + 1, mid + 1, right, ql, qr);
    }

    int first(int left, int right) const {
        return first(1, 0, limit, left, right);
    }

    int last(int node, int left, int right, int ql, int qr) const {
        if (qr < left || right < ql || tree[node] == 0) return -1;
        if (left == right) return left;
        int mid = (left + right) / 2;
        int pos = last(node * 2 + 1, mid + 1, right, ql, qr);
        if (pos != -1) return pos;
        return last(node * 2, left, mid, ql, qr);
    }

    int last(int left, int right) const {
        return last(1, 0, limit, left, right);
    }
};

int upper, bestAmb;
bool changed;
SegTree reachTree;
vector<unsigned char> reachable, rootWays;
vector<int> values;

int parseExpr(Constructor &ctor) {
    string token;
    cin >> token;
    if (token == "(") {
        int left = parseExpr(ctor);
        string op;
        cin >> op;
        int right = parseExpr(ctor);
        cin >> token;
        int id = ctor.nodes.size();
        ctor.nodes.push_back({op == "+" ? 2 : 3, 0, left, right});
        return id;
    }
    int id = ctor.nodes.size(), value = 0;
    if (token[0] == 'x') {
        for (int i = 1; i < (int)token.size(); ++i) value = value * 10 + token[i] - '0';
        ctor.nodes.push_back({0, value - 1, -1, -1});
    } else {
        for (char ch : token) value = min(upper + 1, value * 10 + ch - '0');
        ctor.nodes.push_back({1, value, -1, -1});
    }
    return id;
}

int evalExpr(const Constructor &ctor, int id, const array<int, 5> &args) {
    const ExprNode &node = ctor.nodes[id];
    if (node.type == 0) return args[node.value];
    if (node.type == 1) return node.value;
    int left = evalExpr(ctor, node.left, args), right = evalExpr(ctor, node.right, args);
    if (node.type == 2) return min(upper + 1, left + right);
    return min(1LL * upper + 1, 1LL * left * right);
}

void addReach(int value) {
    if (reachable[value]) return;
    reachable[value] = 1;
    reachTree.add(value);
    changed = true;
}

void searchReach(const Constructor &ctor, array<int, 5> low, array<int, 5> high) {
    int splitId = -1, maxWidth = 0;
    for (int i = 0; i < ctor.arity; ++i) {
        int left = reachTree.first(low[i], high[i]);
        if (left == -1) return;
        int right = reachTree.last(low[i], high[i]);
        low[i] = left;
        high[i] = right;
        if (right - left > maxWidth) {
            maxWidth = right - left;
            splitId = i;
        }
    }
    int minVal = evalExpr(ctor, ctor.root, low);
    if (minVal > upper) return;
    int maxVal = evalExpr(ctor, ctor.root, high), rightVal = min(upper, maxVal);
    if (reachTree.count(minVal, rightVal) == rightVal - minVal + 1) return;
    if (minVal == maxVal) {
        addReach(minVal);
        return;
    }
    int mid = (low[splitId] + high[splitId]) / 2, oldHigh = high[splitId];
    high[splitId] = mid;
    searchReach(ctor, low, high);
    high[splitId] = oldHigh;
    low[splitId] = mid + 1;
    searchReach(ctor, low, high);
}

void addWays(int value, int count) {
    rootWays[value] = min(2, rootWays[value] + count);
    if (rootWays[value] == 2) bestAmb = min(bestAmb, value);
}

void searchAmb(const Constructor &ctor, array<int, 5> low, array<int, 5> high) {
    array<int, 5> minArgs = {}, maxArgs = {};
    int splitId = -1, maxWidth = 0;
    for (int i = 0; i < ctor.arity; ++i) {
        minArgs[i] = values[low[i]];
        maxArgs[i] = values[high[i]];
        if (high[i] - low[i] > maxWidth) {
            maxWidth = high[i] - low[i];
            splitId = i;
        }
    }
    int minVal = evalExpr(ctor, ctor.root, minArgs);
    if (minVal >= bestAmb) return;
    int maxVal = evalExpr(ctor, ctor.root, maxArgs);
    if (minVal == maxVal) {
        int count = 1;
        for (int i = 0; i < ctor.arity; ++i) count = min(2, count * (high[i] - low[i] + 1));
        addWays(minVal, count);
        return;
    }
    int mid = (low[splitId] + high[splitId]) / 2, oldHigh = high[splitId];
    high[splitId] = mid;
    searchAmb(ctor, low, high);
    high[splitId] = oldHigh;
    low[splitId] = mid + 1;
    searchAmb(ctor, low, high);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int lower, baseCount, ctorCount;
    bool firstCase = true;
    while (cin >> lower >> upper) {
        cin >> baseCount >> ctorCount;
        vector<int> arities(ctorCount), baseValues(baseCount);
        for (int &arity : arities) cin >> arity;
        reachable.assign(upper + 1, 0);
        rootWays.assign(upper + 1, 0);
        reachTree.init(upper);
        bestAmb = upper + 1;
        changed = false;
        for (int &value : baseValues) {
            cin >> value;
            addReach(value);
            addWays(value, 1);
        }
        vector<Constructor> ctors(ctorCount);
        for (int i = 0; i < ctorCount; ++i) {
            ctors[i].arity = arities[i];
            ctors[i].root = parseExpr(ctors[i]);
        }
        array<int, 5> low = {}, high = {};
        high.fill(upper);
        do {
            changed = false;
            for (const Constructor &ctor : ctors) searchReach(ctor, low, high);
        } while (changed);
        values.clear();
        int incomplete = -1;
        for (int value = 0; value <= upper; ++value) {
            if (reachable[value]) values.push_back(value);
            else if (value >= lower && incomplete == -1) incomplete = value;
        }
        low.fill(0);
        high.fill((int)values.size() - 1);
        for (const Constructor &ctor : ctors) searchAmb(ctor, low, high);
        if (!firstCase) cout << '\n';
        firstCase = false;
        if (incomplete == -1 && bestAmb > upper) cout << "REGULAR\n";
        else {
            if (incomplete != -1) cout << "INCOMPLETE " << incomplete << '\n';
            if (bestAmb <= upper) cout << "AMBIGUOUS " << bestAmb << '\n';
        }
    }
    return 0;
}
