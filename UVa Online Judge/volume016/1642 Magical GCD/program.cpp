// Magical GCD
// UVa ID: 1642
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

#define LCHILD(x) ((x << 1) | 1)
#define RCHILD(x) ((x + 1) << 1)

struct node
{
    long long r, magicalGCD, gcd, L;
} st[MAXN * 4];

int n;
long long data[MAXN];

void pushUp(int p)
{
    st[p].gcd = __gcd(st[LCHILD(p)].gcd, st[RCHILD(p)].gcd);
    st[p].L = st[LCHILD(p)].L + st[RCHILD(p)].L;
    st[p].magicalGCD = st[p].gcd * st[p].L;
    st[p].r = max(st[p].magicalGCD, max(st[LCHILD(p)].r, st[RCHILD(p)].r));
}

void build(int p, int left, int right)
{
    if (left == right) st[p].magicalGCD = st[p].gcd = data[left], st[p].L = 1;
    else
    {
        int middle = (left + right) >> 1;
        build(LCHILD(p), left, middle);
        build(RCHILD(p), middle + 1, right);
        pushUp(p);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> data[i];
        build(0, 0, n - 1);
        cout << st[0].r << '\n';
    }

    return 0;
}
