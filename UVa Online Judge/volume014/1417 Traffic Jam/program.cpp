#include <bits/stdc++.h>
using namespace std;

struct RollbackDsu {
    vector<int> parent, size;
    vector<pair<int, int> > history;

    RollbackDsu(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int findRoot(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    void mergeSet(int a, int b) {
        a = findRoot(a);
        b = findRoot(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        history.push_back(make_pair(a, b));
        parent[b] = a;
        size[a] += size[b];
    }

    int getState() {
        return history.size();
    }

    void rollback(int state) {
        while ((int)history.size() > state) {
            int a = history.back().first, b = history.back().second;
            history.pop_back();
            parent[b] = b;
            size[a] -= size[b];
        }
    }
};

struct Query {
    int type, a, b;
};

int col, opCount;
vector<vector<pair<int, int> > > tree;
vector<Query> queries;
vector<char> answers;
RollbackDsu *dsu;

void addEdge(int node, int left, int right, int start, int end, pair<int, int> edge) {
    if (start <= left && right <= end) {
        tree[node].push_back(edge);
        return;
    }
    int mid = (left + right) >> 1;
    if (start <= mid) addEdge(node << 1, left, mid, start, end, edge);
    if (end > mid) addEdge(node << 1 | 1, mid + 1, right, start, end, edge);
}

void solveTree(int node, int left, int right) {
    int state = dsu->getState();
    for (int i = 0; i < (int)tree[node].size(); i++) dsu->mergeSet(tree[node][i].first, tree[node][i].second);
    if (left == right) {
        if (queries[left].type == 1) {
            if (dsu->findRoot(queries[left].a) == dsu->findRoot(queries[left].b)) answers[left] = 'Y';
            else answers[left] = 'N';
        }
    } else {
        int mid = (left + right) >> 1;
        solveTree(node << 1, left, mid);
        solveTree(node << 1 | 1, mid + 1, right);
    }
    dsu->rollback(state);
}

long long getKey(int a, int b) {
    if (a > b) swap(a, b);
    return 1LL * a * (2 * col) + b;
}

int getId(int row, int column) {
    return (row - 1) * col + column - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> col;
        string command;
        int r1, c1, r2, c2;
        opCount = 0;
        queries.clear();
        unordered_map<long long, int> openTime;
        unordered_map<long long, pair<int, int> > edgeInfo;
        vector<tuple<int, int, pair<int, int> > > intervals;
        while (cin >> command) {
            if (command == "Exit") break;
            cin >> r1 >> c1 >> r2 >> c2;
            int a = getId(r1, c1), b = getId(r2, c2);
            long long key = getKey(a, b);
            if (command == "Open") {
                openTime[key] = opCount;
                edgeInfo[key] = make_pair(a, b);
                queries.push_back({0, 0, 0});
            } else if (command == "Close") {
                int start = openTime[key];
                intervals.push_back(make_tuple(start, opCount, edgeInfo[key]));
                openTime.erase(key);
                queries.push_back({0, 0, 0});
            } else {
                queries.push_back({1, a, b});
            }
            opCount++;
        }
        for (unordered_map<long long, int>::iterator it = openTime.begin(); it != openTime.end(); it++)
            intervals.push_back(make_tuple(it->second, opCount, edgeInfo[it->first]));
        if (opCount == 0) continue;
        tree.assign(opCount * 4 + 5, vector<pair<int, int> >());
        for (int i = 0; i < (int)intervals.size(); i++) {
            int start = get<0>(intervals[i]), end = get<1>(intervals[i]);
            if (start < end) addEdge(1, 0, opCount - 1, start, end - 1, get<2>(intervals[i]));
        }
        answers.assign(opCount, 'N');
        RollbackDsu curDsu(2 * col);
        dsu = &curDsu;
        solveTree(1, 0, opCount - 1);
        for (int i = 0; i < opCount; i++)
            if (queries[i].type == 1) cout << answers[i] << '\n';
    }
    return 0;
}
