// Ray Pass Me the Dishes
// UVa ID: 1400
// Verdict: Accepted
// Submission Date: 2019-01-13
// UVa Run Time: 0.130s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500010;

long long dishes[MAXN];
struct NODE
{
    long long sum, prefix, suffix, sub;
    int pend, sstart, astart, aend;
} st[4 * MAXV];

NODE combine(NODE a, NODE b)
{
    if (a.pend == -1) return b;
    if (b.pend == -1) return a;

    NODE nd;

    nd.sum = a.sum + b.sum;

    if (a.prefix >= a.sum + b.prefix)
    {
        nd.prefix = a.prefix;
        nd.pend = a.pend;
    }
    else
    {
        nd.prefix = a.sum + b.prefix;
        nd.pend = b.pend;
    }

    if (a.suffix + b.sum >= b.suffix)
    {
        nd.suffix = a.suffix + b.sum;
        nd.sstart = a.sstart;
    }
    else
    {
        nd.suffix = b.suffix;
        nd.sstart = b.sstart;
    }
    
    if (a.sub >= b.sub)
    {
        nd.sub = a.sub;
        nd.astart = a.astart, nd.aend = a.aend;
    }
    else
    {
        nd.sub = b.sub;
        nd.astart = b.astart, nd.aend = b.aend;
    }

    if (a.suffix + b.prefix > nd.sub)
    {
        nd.sub = a.suffix + b.prefix;
        nd.astart = a.sstart, nd.aend = b.pend;
    }
    else if (a.suffix + b.prefix == nd.sub)
    {
        if (a.sstart < nd.astart || (a.sstart == nd.astart && b.pend < nd.aend))
            nd.astart = a.sstart, nd.aend = b.pend;
    }

    return nd;
}

NODE getData(long long value, int idx)
{
    NODE nd;
    nd.sum = value;
    nd.prefix = nd.suffix = nd.sub = value;
    nd.pend = nd.sstart = nd.astart = nd.aend = idx;
    return nd;
}

void build(int p, int left, int right)
{
    if (left > right) return;
    if (left == right) st[p] = getData(dishes[left], left);
    else
    {
        int middle = (left + right) >> 1;
        build((p << 1) | 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        st[p] = combine(st[(p << 1) | 1], st[(p + 1) << 1]);
    }
}

NODE query(int p, int left, int right, int qleft, int qright)
{
    if (left > right) return getData(0, -1);
    if (left > qright || right < qleft) return getData(0, -1);
    if (left >= qleft && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    NODE q1 = query((p << 1) | 1, left, middle, qleft, qright);
    NODE q2 = query((p + 1) << 1, middle + 1, right, qleft, qright);
    return combine(q1, q2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, qleft, qright, cases = 0;
    while (cin >> n >> m)
    {
        cout << "Case " << ++cases << ":\n";
        for (int i = 0; i < n; i++) cin >> dishes[i];
        build(0, 0, n - 1);
        for (int i = 0; i < m; i++)
        {
            cin >> qleft >> qright;
            qleft--, qright--;
            NODE q = query(0, 0, n - 1, qleft, qright);
            cout << (q.astart + 1) << ' ' << (q.aend + 1) << '\n';
        }
    }

    return 0;
}
