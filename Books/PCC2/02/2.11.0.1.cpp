#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x7f7f7f7f;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

int data[MAXN];
struct node { int field; } st[4 * MAXN];

void pushUp(int p)
{
    st[p].field = max(st[LC(p)].field, st[RC(p)].field);
}

void build(int p, int left, int right)
{
    if (left == right) st[p].field = data[left];
    else {
        int middle = (left + right) >> 1;
        build(LC(p), left, middle);
        build(RC(p), middle + 1, right);
        pushUp(p);
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (left > qright || right < qleft) return -INF;
    if (left >= qleft && right <= qright) return st[p].field;
    int middle = (left + right) >> 1;
    int q1 = query(LC(p), left, middle, qleft, qright);
    int q2 = query(RC(p), middle + 1, right, qleft, qright);
    return max(q1, q2);
}

void update(int p, int left, int right, int index, int value)
{
    if (left == right) st[p].field = value;
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
