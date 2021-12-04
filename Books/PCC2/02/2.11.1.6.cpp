#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x7f7f7f7f;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

struct node { int sum, prefix, suffix, sub; } st[4 * MAXN];

node combine(node a, node b)
{
    if (a.sum == -INF) return b;
    if (b.sum == -INF) return a;
    node nd;
    nd.sum = a.sum + b.sum;
    nd.prefix = max(a.prefix, a.sum + b.prefix);
    nd.suffix = max(b.suffix, b.sum + a.suffix);
    nd.sub = max(max(a.sub, b.sub), a.suffix + b.prefix);
    return nd;
}

node getData(int value)
{
    node nd;
    nd.sum = nd.prefix = nd.suffix = nd.sub = value;
    return nd;
}

void pushUp(int p)
{
    st[p] = combine(st[LC(p)], st[RC(p)]);
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
