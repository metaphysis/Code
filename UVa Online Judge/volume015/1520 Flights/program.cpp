#include <bits/stdc++.h>
using namespace std;

const double NegInf = -1e100;

struct Missile {
    int p, topX, y, rightX;
    double a, b, c;
};

struct Query {
    int t1, t2, x1, x2;
};

struct Line {
    double a, b, c;
    bool used;
    Line() : a(0), b(0), c(0), used(false) {}
    Line(double aa, double bb, double cc) : a(aa), b(bb), c(cc), used(true) {}
    double get(double x) const {
        return a * x * x + b * x + c;
    }
};

int n, m, timeSize;
vector<Missile> missiles;
vector<Query> queries;
vector<vector<int>> timeMis, timeQue;
vector<double> answers;

void addMissile(int node, int l, int r, int pos, int id) {
    timeMis[node].push_back(id);
    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid) addMissile(node * 2, l, mid, pos, id);
    else addMissile(node * 2 + 1, mid + 1, r, pos, id);
}

struct LiChao {
    vector<int> xs;
    vector<Line> tree;
    int size;

    LiChao(const vector<int> &values) {
        xs = values;
        size = (int)xs.size();
        tree.assign(size * 4 + 5, Line());
    }

    void insertLine(int node, int l, int r, Line line) {
        if (!tree[node].used) {
            tree[node] = line;
            return;
        }
        int mid = (l + r) / 2;
        bool leftBetter = line.get(xs[l]) > tree[node].get(xs[l]);
        bool midBetter = line.get(xs[mid]) > tree[node].get(xs[mid]);
        if (midBetter) swap(line, tree[node]);
        if (l == r) return;
        if (leftBetter != midBetter) insertLine(node * 2, l, mid, line);
        else insertLine(node * 2 + 1, mid + 1, r, line);
    }

    void insertSegment(int node, int l, int r, int ql, int qr, Line line) {
        if (ql <= l && r <= qr) {
            insertLine(node, l, r, line);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) insertSegment(node * 2, l, mid, ql, qr, line);
        if (qr > mid) insertSegment(node * 2 + 1, mid + 1, r, ql, qr, line);
    }

    void insertSegment(int left, int right, Line line) {
        if (left <= right && size > 0) insertSegment(1, 0, size - 1, left, right, line);
    }

    double query(int node, int l, int r, int pos) const {
        double result = tree[node].used ? tree[node].get(xs[pos]) : NegInf;
        if (l == r) return result;
        int mid = (l + r) / 2;
        if (pos <= mid) result = max(result, query(node * 2, l, mid, pos));
        else result = max(result, query(node * 2 + 1, mid + 1, r, pos));
        return result;
    }

    double query(int pos) const {
        if (size == 0) return NegInf;
        return query(1, 0, size - 1, pos);
    }
};

int getRangeMax(const vector<int> &tree, int size, int left, int right) {
    int result = 0;
    left += size;
    right += size;
    while (left <= right) {
        if (left & 1) result = max(result, tree[left++]);
        if (!(right & 1)) result = max(result, tree[right--]);
        left >>= 1;
        right >>= 1;
    }
    return result;
}

void processNode(int node) {
    if (timeQue[node].empty()) return;
    vector<int> coords;
    for (int qid : timeQue[node]) {
        coords.push_back(queries[qid].x1);
        coords.push_back(queries[qid].x2);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    LiChao liChao(coords);
    for (int id : timeMis[node]) {
        int left = lower_bound(coords.begin(), coords.end(), missiles[id].p) - coords.begin();
        int right = upper_bound(coords.begin(), coords.end(), missiles[id].rightX) - coords.begin() - 1;
        liChao.insertSegment(left, right, Line(missiles[id].a, missiles[id].b, missiles[id].c));
    }
    vector<pair<int, int>> tops;
    tops.reserve(timeMis[node].size());
    for (int id : timeMis[node]) tops.push_back({missiles[id].topX, missiles[id].y});
    sort(tops.begin(), tops.end());
    vector<int> topX(tops.size()), topY(tops.size());
    for (int i = 0; i < (int)tops.size(); i++) {
        topX[i] = tops[i].first;
        topY[i] = tops[i].second;
    }
    int topSize = 1;
    while (topSize < (int)topY.size()) topSize <<= 1;
    vector<int> topTree(topSize * 2, 0);
    for (int i = 0; i < (int)topY.size(); i++) topTree[topSize + i] = topY[i];
    for (int i = topSize - 1; i >= 1; i--) topTree[i] = max(topTree[i * 2], topTree[i * 2 + 1]);
    for (int qid : timeQue[node]) {
        int l = lower_bound(topX.begin(), topX.end(), queries[qid].x1) - topX.begin();
        int r = upper_bound(topX.begin(), topX.end(), queries[qid].x2) - topX.begin() - 1;
        double result = 0;
        if (l <= r) result = max(result, (double)getRangeMax(topTree, topSize, l, r));
        int p1 = lower_bound(coords.begin(), coords.end(), queries[qid].x1) - coords.begin();
        int p2 = lower_bound(coords.begin(), coords.end(), queries[qid].x2) - coords.begin();
        result = max(result, liChao.query(p1));
        result = max(result, liChao.query(p2));
        answers[qid] = max(answers[qid], result);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> n) {
        missiles.clear();
        queries.clear();
        timeMis.clear();
        timeQue.clear();
        answers.clear();
        missiles.resize(n);
        timeSize = 1;
        while (timeSize < n) timeSize <<= 1;
        timeMis.resize(timeSize * 2);
        for (int i = 0; i < n; i++) {
            int p, x, y;
            cin >> p >> x >> y;
            int d = x - p;
            int rightX = 2 * x - p;
            double k = (double)y / d / d;
            missiles[i] = {p, x, y, rightX, -k, 2.0 * k * x, y - k * x * x};
            addMissile(1, 1, timeSize, i + 1, i);
        }
        cin >> m;
        queries.resize(m);
        answers.assign(m, 0);
        for (int i = 0; i < m; i++)
            cin >> queries[i].t1 >> queries[i].t2 >> queries[i].x1 >> queries[i].x2;
        timeQue.resize(timeSize * 2);
        for (int i = 0; i < m; i++) {
            int left = queries[i].t1 + timeSize - 1;
            int right = queries[i].t2 + timeSize - 1;
            while (left <= right) {
                if (left & 1) timeQue[left++].push_back(i);
                if (!(right & 1)) timeQue[right--].push_back(i);
                left >>= 1;
                right >>= 1;
            }
        }
        for (int i = 1; i < timeSize * 2; i++) processNode(i);
        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << fixed << setprecision(6);
        for (double answer : answers) cout << answer << '\n';
    }
    return 0;
}
