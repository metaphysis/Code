const int MAXN = 100010, INF = 0x7f7f7f7f;

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

void build(int data[], int p, int left, int right)
{
    if (left > right) return;
    if (left == right) st[p] = getData(data[left]);
    else {
        int middle = (left + right) >> 1;
        build(data, (p << 1) | 1, left, middle);
        build(data, (p + 1) << 1, middle + 1, right);
        st[p] = combine(st[(p << 1) | 1], st[(p + 1) << 1]);
    }
}

void update(int p, int left, int right, int index, int value)
{
    if (index < left || index > right) return;
    if (index == left && index == right) st[p] = getData(value);
    else {
        int middle = (left + right) >> 1;
        update((p << 1) | 1, left, middle, index, value);
        update((p + 1) << 1, middle + 1, right, index, value);
        st[p] = combine(st[(p << 1) | 1], st[(p + 1) << 1]);
    }
}

node query(int p, int left, int right, int qleft, int qright)
{
    if (left > right) return getData(-INF);
    if (left > qright || right < qleft) return getData(-INF);
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    node q1 = query((p << 1) | 1, left, middle, qleft, qright);
    node q2 = query((p + 1) << 1, middle + 1, right, qleft, qright);
    return combine(q1, q2);
}
