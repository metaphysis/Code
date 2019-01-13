#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, INF = 0x7f7f7f7f;

pair<int, int> st[4 * MAXN];

pair<int, int> combine(pair<int, int> a, pair<int, int> b)
{
    if (a.first > b.first) return a;
    if (b.first > a.first) return b;
    return make_pair(a.first, a.second + b.second);
}

void build(int data[], int p, int left, int right)
{
    if (left > right) return;
    if (left == right) st[p] = make_pair(data[left], 1);
    else {
        int middle = (left + right) >> 1;
        build(data, (p << 1) | 1, left, middle);
        build(data, (p + 1) << 1, middle + 1, right);
        st[p] = combine(st[(p << 1) | 1], st[(p + 1) << 1]);
    }
}

pair<int, int> query(int p, int left, int right, int qleft, int qright)
{
    if (left > right) return make_pair(-INF, 0);
    if (left > qright || right < qleft) return make_pair(-INF, 0);
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    pair<int, int> q1 = query((p << 1) | 1, left, middle, qleft, qright);
    pair<int, int> q2 = query((p + 1) << 1, middle + 1, right, qleft, qright);
    return combine(q1, q2);
}

void update(int p, int left, int right, int index, int value)
{
    if (index < left || index > right) return;
    if (index == left && index == right) st[p] = make_pair(value, 1);
    else {
        int middle = (left + right) >> 1;
        update((p << 1) | 1, left, middle, index, value);
        update((p + 1) << 1, middle + 1, right, index, value);
        st[p] = combine(st[(p << 1) | 1], st[(p + 1) << 1]);
    }
}
