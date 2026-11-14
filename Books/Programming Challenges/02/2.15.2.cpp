#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;

struct update { int pos, oldVal, newVal; };

struct query { int l, r, t, idx; };

int n, m, blockSize;

int data[MAXN], last[MAXN], answer[MAXN], cnt[MAXN], currentAnswer;

vector<update> updates;
vector<query> queries;

// 查询比较函数。
bool cmp(query a, query b) {
    if (a.l / blockSize != b.l / blockSize)
        return a.l / blockSize < b.l / blockSize;
    if (a.r / blockSize != b.r / blockSize)
        return a.r / blockSize < b.r / blockSize;
    return a.t < b.t;
}

// 扩展区间，pos为待操作的数组元素下标。
void add(int pos) {
    cnt[data[pos]]++;
    if (cnt[data[pos]] == 1) currentAnswer++;
}

// 收缩区间，pos为待操作的数组元素下标。
void remove(int pos) {
    cnt[data[pos]]--;
    if (cnt[data[pos]] == 0) currentAnswer--;
}

// 根据实际情况实现更新应用逻辑，此处以统计不同元素个数为例。
void applyUpdate(int curL, int curR, int pos, int val) {
    if (curL <= pos && pos <= curR) {
        remove(pos);
        data[pos] = val;
        add(pos);
    } else data[pos] = val;
}

// 带修莫队。
void moWithUpdates() {
    blockSize = pow(n, 2.0/3.0);
    sort(queries.begin(), queries.end(), cmp);
    int curL = 0, curR = -1, curT = 0;
    for (auto q : queries) {
        while (curT < q.t) {
            applyUpdate(curL, curR, updates[curT].pos, updates[curT].newVal);
            curT++;
        }
        while (curT > q.t) {
            curT--;
            applyUpdate(curL, curR, updates[curT].pos, updates[curT].oldVal);
        }
        while (curL > q.l) add(--curL);
        while (curR < q.r) add(++curR);
        while (curL < q.l) remove(curL++);
        while (curR > q.r) remove(curR--);
        answer[q.idx] = currentAnswer;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        last[i] = data[i];
    }
    int clocks = 0, idx = 0;
    int command, l, r, p, v;
    for (int i = 0; i < m; i++) {
        cin >> command;
        if (command == 0) {
            cin >> p >> v;
            updates.push_back(update{p, last[p], v});
            last[p] = v;
            clocks++;
        }
        if (command == 1) {
            cin >> l >> r;
            queries.push_back(query{l, r, clocks, idx++});
        }
    }
    moWithUpdates();
    for (int i = 0; i < idx; i++) cout << answer[i] << '\n';
    return 0;
}
