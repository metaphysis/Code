#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x7f7f7f7f;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

pair<int, int> st[4 * MAXN];

pair<int, int> combine(pair<int, int> a, pair<int, int> b)
{
    if (a.first > b.first) return a;
    if (b.first > a.first) return b;
    return make_pair(a.first, a.second + b.second);
}

void pushUp(int p)
{
    st[p] = combine(st[LC(p)], st[RC(p)]);
}

void build(int data[], int p, int left, int right)
{
    if (left == right) st[p] = make_pair(data[left], 1);
    else {
        int middle = (left + right) >> 1;
        build(data, LC(p), left, middle);
        build(data, RC(p), middle + 1, right);
        pushUp(p);
    }
}

pair<int, int> query(int p, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft) return make_pair(-INF, 0);
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    pair<int, int> q1 = query(LC(p), left, middle, qleft, qright);
    pair<int, int> q2 = query(RC(p), middle + 1, right, qleft, qright);
    return combine(q1, q2);
}

void update(int p, int left, int right, int index, int value)
{
    if (left == right) st[p] = make_pair(value, 1);
    else {
        int middle = (left + right) >> 1;
        if (index <= middle)
            update(LC(p), left, middle, index, value);
        else
            update(RC(p), middle + 1, right, index, value);
        pushUp(p);
    }
}

int main(int argc, char *argv[])
{
    return 0;
}
