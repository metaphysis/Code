#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x7f7f7f7f;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

struct node { int sum, prefix, suffix, sub; } st[4 * MAXN];

node getData(int value)
{
    node nd;
    nd.sum = nd.sub = value;
    nd.prefix = nd.suffix = max(value, 0);
    return nd;
}

void pushUp(int p)
{
    node a = st[LC(p)], b = st[RC(p)];
    st[p].sum = a.sum + b.sum;
    st[p].sub = max(max(a.sub, b.sub), a.suffix + st[p].value + b.prefix);
    st[p].prefix = max(a.prefix, a.sum + st[p].value + b.prefix);
    st[p].suffix = max(b.suffix, a.suffix + st[p].value + b.sum);
}

void build(int data[], int p, int left, int right)
{
    if (left == right) st[p] = getData(data[left]);
    else {
        int middle = (left + right) >> 1;
        build(data, LC(p), left, middle);
        build(data, RC(p), middle + 1, right);
        pushUp(p);
    }
}

node query(int p, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft) return getData(-INF);
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    node q1 = query(LC(p), left, middle, qleft, qright);
    node q2 = query(RC(p), middle + 1, right, qleft, qright);
    return combine(q1, q2);
}

void update(int p, int left, int right, int index, int value)
{
    if (left == right) st[p] = getData(value);
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
