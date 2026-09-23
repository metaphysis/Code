#include <bits/stdc++.h>
using namespace std;

const int maxBit = 1005;

using BitSet = bitset<maxBit>;

vector<vector<BitSet>> segTree;
vector<BitSet> basis;
vector<int> history;
vector<BitSet> answerList;

void insertValue(const BitSet &value) {
    BitSet current = value;
    for (int i = maxBit - 1; i >= 0; --i) {
        if (!current[i]) continue;
        if (basis[i].none()) {
            basis[i] = current;
            history.push_back(i);
            return;
        }
        current ^= basis[i];
    }
}

void addInterval(int node, int left, int right, int queryLeft, int queryRight, const BitSet &value) {
    if (queryLeft <= left && right <= queryRight) {
        segTree[node].push_back(value);
        return;
    }
    int middle = (left + right) / 2;
    if (queryLeft <= middle) addInterval(node * 2, left, middle, queryLeft, queryRight, value);
    if (queryRight > middle) addInterval(node * 2 + 1, middle + 1, right, queryLeft, queryRight, value);
}

BitSet getMaxValue() {
    BitSet result;
    for (int i = maxBit - 1; i >= 0; --i)
        if (basis[i].any() && !result[i]) result ^= basis[i];
    return result;
}

void printValue(const BitSet &value) {
    bool started = false;
    for (int i = maxBit - 1; i >= 0; --i) {
        if (value[i]) {
            started = true;
            cout << '1';
        } else if (started) {
            cout << '0';
        }
    }
    if (!started) cout << '0';
    cout << '\n';
}

void solveSegmentTree(int node, int left, int right) {
    int checkpoint = history.size(), pivot;
    for (const BitSet &value : segTree[node]) insertValue(value);
    if (left == right) {
        printValue(getMaxValue());
    } else {
        int middle = (left + right) / 2;
        solveSegmentTree(node * 2, left, middle);
        solveSegmentTree(node * 2 + 1, middle + 1, right);
    }
    while (history.size() > checkpoint) {
        pivot = history.back();
        history.pop_back();
        basis[pivot].reset();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int, BitSet>>> changes(n + 1);
        vector<BitSet> currentValue(n + 1);
        for (int i = 1; i <= n; ++i) changes[i].push_back({1, currentValue[i]});
        for (int time = 1; time <= m; ++time) {
            int x, y;
            string word;
            cin >> x >> y >> word;
            BitSet weight;
            for (int i = 0; i < word.size(); ++i)
                if (word[word.size() - 1 - i] == '1') weight[i] = 1;
            BitSet oldX = currentValue[x], oldY = currentValue[y];
            currentValue[x] ^= weight;
            currentValue[y] ^= weight;
            if (currentValue[x] != oldX) changes[x].push_back({time, currentValue[x]});
            if (currentValue[y] != oldY) changes[y].push_back({time, currentValue[y]});
        }
        segTree.assign(4 * (m + 5), vector<BitSet>());
        for (int vertex = 1; vertex <= n; ++vertex) {
            for (int i = 0; i < changes[vertex].size(); ++i) {
                int left = changes[vertex][i].first;
                int right = m;
                if (i + 1 < changes[vertex].size()) right = changes[vertex][i + 1].first - 1;
                if (left <= right && changes[vertex][i].second.any())
                    addInterval(1, 1, m, left, right, changes[vertex][i].second);
            }
        }
        basis.assign(maxBit, BitSet());
        history.clear();
        solveSegmentTree(1, 1, m);
    }
    return 0;
}
