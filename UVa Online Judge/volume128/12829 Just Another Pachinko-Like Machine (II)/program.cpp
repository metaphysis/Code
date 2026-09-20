#include <bits/stdc++.h>
using namespace std;

struct Bar {
    long long x1, x2, y, score;
    int delay;
};

class Solver {
private:
    vector<long long> coords;
    vector<vector<pair<long long, int>>> tree;
    vector<char> active;
    vector<Bar> bars;

    void addBar(int node, int left, int right, int ql, int qr, int id) {
        if (ql <= left && right <= qr) {
            tree[node].push_back({bars[id].y, id});
            return;
        }
        int mid = (left + right) / 2;
        if (ql <= mid)
            addBar(node * 2, left, mid, ql, qr, id);
        if (qr > mid)
            addBar(node * 2 + 1, mid + 1, right, ql, qr, id);
    }

    void sortTree(int node, int left, int right) {
        sort(tree[node].begin(), tree[node].end());
        if (left == right)
            return;
        int mid = (left + right) / 2;
        sortTree(node * 2, left, mid);
        sortTree(node * 2 + 1, mid + 1, right);
    }

    pair<long long, int> queryTree(int node, int left, int right, int pos, long long limitY) {
        pair<long long, int> result = {-1, -1};
        auto it = lower_bound(tree[node].begin(), tree[node].end(), make_pair(limitY, -1));
        if (it != tree[node].begin()) {
            --it;
            result = *it;
        }
        if (left == right)
            return result;
        int mid = (left + right) / 2;
        pair<long long, int> childResult;
        if (pos <= mid)
            childResult = queryTree(node * 2, left, mid, pos, limitY);
        else
            childResult = queryTree(node * 2 + 1, mid + 1, right, pos, limitY);
        if (childResult.first > result.first)
            result = childResult;
        return result;
    }

public:
    void init(vector<Bar> inputBars) {
        bars = inputBars;
        int n = bars.size();
        coords.clear();
        coords.reserve(n * 2);
        for (const Bar &bar : bars) {
            coords.push_back(bar.x1);
            coords.push_back(bar.x2 + 1);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        int size = coords.size();
        tree.assign(size * 4 + 5, {});
        active.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            int left = lower_bound(coords.begin(), coords.end(), bars[i].x1) - coords.begin();
            int right = lower_bound(coords.begin(), coords.end(), bars[i].x2 + 1) - coords.begin() - 1;
            addBar(1, 0, size - 1, left, right, i);
        }
        sortTree(1, 0, size - 1);
    }

    int getPosition(long long x) {
        int pos = upper_bound(coords.begin(), coords.end(), x) - coords.begin() - 1;
        if (pos < 0 || pos >= static_cast<int>(coords.size()) - 1)
            return -1;
        return pos;
    }

    pair<long long, int> query(long long x, long long y) {
        int pos = getPosition(x);
        if (pos == -1)
            return {-1, -1};
        pair<long long, int> result = queryTree(1, 0, coords.size() - 1, pos, y);
        while (result.second != -1 && !active[result.second]) {
            y = result.first;
            result = queryTree(1, 0, coords.size() - 1, pos, y);
        }
        return result;
    }

    void solveCase(int caseId) {
        int b;
        cin >> b;
        vector<vector<int>> recover(b + 6);
        long long totalScore = 0;
        cout << "Case " << caseId << ":\n";
        for (int step = 1; step <= b; ++step) {
            for (int id : recover[step])
                active[id] = 1;
            long long inputX, inputY;
            cin >> inputX >> inputY;
            long long x = inputX ^ totalScore;
            long long y = inputY ^ totalScore;
            pair<long long, int> result = query(x, y);
            if (result.second != -1) {
                int id = result.second;
                totalScore += bars[id].score;
                active[id] = 0;
                recover[step + bars[id].delay].push_back(id);
            }
            cout << totalScore << '\n';
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseId = 0;
    while (cin >> n) {
        vector<Bar> bars(n);
        for (Bar &bar : bars)
            cin >> bar.x1 >> bar.x2 >> bar.y >> bar.score >> bar.delay;
        Solver solver;
        solver.init(bars);
        solver.solveCase(++caseId);
    }
    return 0;
}
