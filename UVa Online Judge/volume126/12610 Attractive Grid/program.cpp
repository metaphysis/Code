#include <bits/stdc++.h>
using namespace std;

struct Operation {
    int r, l, rr, color, rank;
};

struct Event {
    long long pos;
    int id, type;
};

struct Fenwick {
    int n;
    vector<int> tree;
    Fenwick(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    void add(int index, int value) {
        while (index <= n) {
            tree[index] += value;
            index += index & -index;
        }
    }
    int kth(int target) {
        int index = 0, step = 1;
        while ((step << 1) <= n) step <<= 1;
        while (step > 0) {
            int next = index + step;
            if (next <= n && tree[next] < target) {
                index = next;
                target -= tree[next];
            }
            step >>= 1;
        }
        return index + 1;
    }
};

long long solveCase(int m, int e, int l, vector<Operation> &ops) {
    if (l == 0) return 1LL * m * m;
    vector<int> values;
    vector<Event> events;
    values.reserve(e);
    events.reserve(2 * e);
    for (int i = 0; i < e; i++) {
        values.push_back(ops[i].r);
        events.push_back({ops[i].l, i, 1});
        events.push_back({1LL * ops[i].rr + 1, i, -1});
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 0; i < e; i++)
        ops[i].rank = lower_bound(values.begin(), values.end(), ops[i].r) - values.begin() + 1;
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        if (a.pos != b.pos) return a.pos < b.pos;
        return a.type < b.type;
    });
    Fenwick fenwick(values.size());
    vector<set<pair<int, int>>> bags(100005);
    long long answer = 0, current = 1;
    int eventIndex = 0, colorCount = 0;
    while (eventIndex < (int)events.size()) {
        long long position = events[eventIndex].pos;
        if (position > m + 1LL) break;
        if (current < position) {
            int height = 0;
            if (colorCount >= l) {
                int index = fenwick.kth(colorCount - l + 1);
                height = values[index - 1];
            }
            answer += (position - current) * height;
            current = position;
        }
        while (eventIndex < (int)events.size() && events[eventIndex].pos == position) {
            int id = events[eventIndex].id, type = events[eventIndex].type;
            Operation &op = ops[id];
            set<pair<int, int>> &bag = bags[op.color];
            int oldValue = bag.empty() ? 0 : bag.rbegin()->first;
            if (type == 1) {
                bag.insert({op.r, id});
            } else {
                bag.erase({op.r, id});
            }
            int newValue = bag.empty() ? 0 : bag.rbegin()->first;
            if (oldValue != newValue) {
                if (oldValue != 0) fenwick.add(lower_bound(values.begin(), values.end(), oldValue) - values.begin() + 1, -1);
                if (newValue != 0) fenwick.add(lower_bound(values.begin(), values.end(), newValue) - values.begin() + 1, 1);
                colorCount += (newValue != 0) - (oldValue != 0);
            }
            eventIndex++;
        }
    }
    if (current <= m) {
        int height = 0;
        if (colorCount >= l) {
            int index = fenwick.kth(colorCount - l + 1);
            height = values[index - 1];
        }
        answer += (m + 1LL - current) * height;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseId = 1; caseId <= t; caseId++) {
        int m, e, l;
        cin >> m >> e >> l;
        vector<Operation> ops(e);
        for (int i = 0; i < e; i++)
            cin >> ops[i].r >> ops[i].l >> ops[i].rr >> ops[i].color;
        cout << "Case " << caseId << ": " << solveCase(m, e, l, ops) << '\n';
    }
    return 0;
}
