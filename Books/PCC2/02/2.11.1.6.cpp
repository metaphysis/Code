#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x7f7f7f7f;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

struct node { int sum, prefix, suffix, sub; } st[4 * MAXN];

node getData(int value) {
    node nd;
    nd.sum = nd.sub = value;
    nd.prefix = nd.suffix = value;
    return nd;
}

node combine(node a, node b) {
    node nd;
    nd.sum = a.sum + b.sum;
    nd.prefix = max(a.prefix, a.sum + b.prefix);
    nd.suffix = max(b.suffix, b.sum + a.suffix);
    nd.sub = max(max(a.sub, b.sub), a.suffix + b.prefix);
    return nd;
}

void pushUp(int p) {
    st[p] = combine(st[LC(p)], st[RC(p)]);
}

void build(int data[], int p, int left, int right) {
    if (left == right) st[p] = getData(data[left]);
    else {
        int middle = (left + right) >> 1;
        build(data, LC(p), left, middle);
        build(data, RC(p), middle + 1, right);
        pushUp(p);
    }
}

node query(int p, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    if (qright <= middle) return query(LC(p), left, middle, qleft, qright);
    if (qleft > middle)   return query(RC(p), middle + 1, right, qleft, qright);
    node q1 = query(LC(p), left, middle, qleft, qright);
    node q2 = query(RC(p), middle + 1, right, qleft, qright);
    return combine(q1, q2);
}

void update(int p, int left, int right, int index, int value) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    static int data[MAXN];
    for (int i = 0; i < n; i++) cin >> data[i];
    build(data, 0, 0, n - 1);
    cout << st[0].sub << '\n';   // 整个数组的最大子段和
    return 0;
}