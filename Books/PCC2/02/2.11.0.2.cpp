struct node { int field, tag; } st[4 * MAXN];

// 应用延迟标记的线段树创建。
void build(int p, int left, int right)
{
    // 在创建线段树时设置初始更新累积量为0，表示此结点不需向其左右子结点传递更新量。
    if (left == right) st[p].field = data[left], st[p].tag = 0;
    // 其他创建线段树的代码与前述相同。
}

// 根据延迟标记对线段树的结点做相应的更改。
void commit(int p, int ctag)
{
    // 可能结点上存在多次的延迟更新，所以要叠加。
    st[p].tag += ctag;
    st[p].field += st[p].tag;
}

// 将延迟标记向左右子结点传递。
void pushDown(int p)
{
    if (st[p].tag) {
        commit(LC(p), st[p].tag);
        commit(RC(p), st[p].tag);
        st[p].tag = 0;
    }
}

// 应用延迟标记的查询。
int query(int p, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft) return -INF;
    if (left >= qleft && right <= qright) return st[p].field;
    // 在查询左右子结点之前需要将延迟标记向下传递。
    pushDown(p);
    int middle = (left + right) >> 1;
    int q1 = query(LC(p), left, middle, qleft, qright);
    int q2 = query(RC(p), middle + 1, right, qleft, qright);
    return max(q1, q2);
}

// 应用延迟标记的更新，将区间内的所有元素改变utag所指定的值。
void update(int p, int left, int right, int uleft, int uright, int utag)
{
    if (left > uright || right < uleft) return;
    if (left >= uleft && right <= uright) commit(p, utag);
    else {
        // 在更新左右子结点之前需要将延迟标记向下传递。
        pushDown(p);
        int middle = (left + right) >> 1;
        update(LC(p), left, middle, uleft, uright, utag);
        update(RC(p), middle + 1, right, uleft, uright, utag);
        pushUp(p);
    }
}
