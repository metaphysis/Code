#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, ADD = 1, DELETE = -1;

#define LCHILD(x) (((x) << 1) | 1)
#define RCHILD(x) (((x) + 1) << 1)

struct rectangle { int x1, y1, x2, y2; } rects[MAXN];
struct event {
    int x, y1, y2, evtCode;
    bool operator<(const event &e) const { return x < e.x; }
} evts[MAXN * 2];
struct node { int cnt, height; } st[4 * MAXN] = {};

int n, id[MAXN *2];

void pushUp(int p, int height)
{
    st[p].height = st[LCHILD(p)].height + st[RCHILD(p)].height;
    if (st[p].cnt) st[p].height = height;
}

void update(int p, int left, int right, int ul, int ur, int value)
{
    if (ul == left && ur == right) st[p].cnt += value;
    else {
        int middle = (left + right) >> 1;
        if (ur <= middle) update(LCHILD(p), left, middle, ul, ur, value);
        else if (ul >= middle) update(RCHILD(p), middle, right, ul, ur, value);
        else {
            update(LCHILD(p), left, middle, ul, middle, value);
            update(RCHILD(p), middle, right, middle, ur, value);
        }
    }
    pushUp(p, id[right] - id[left]);
}

long long getArea()
{
    for (int i = 0; i < n; i++) id[i] = rects[i].y1, id[i + n] = rects[i].y2;
    sort(id, id + 2 * n);
    for (int i = 0; i < 2 * n; i++) {
        rects[i].y1 = lower_bound(id, id + 2 * n, rects[i].y1) - id;
        rects[i].y2 = lower_bound(id, id + 2 * n, rects[i].y2) - id;
    }
    for (int i = 0; i < n; i++) {
        evts[i].evtCode = ADD, evts[i].x = rects[i].x1;
        evts[i + n].evtCode = DELETE, evts[i + n].x = rects[i].x2;
        evts[i].y1 = evts[i + n].y1 = rects[i].y1;
        evts[i].y2 = evts[i + n].y2 = rects[i].y2;
    }
    sort(evts, evts + 2 * n);
    long long area = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i && evts[i].x > evts[i - 1].x)
            area += (long long)(evts[i].x - evts[i - 1].x) * st[0].height;
        update(0, 0, 2 * n - 1, evts[i].y1, evts[i].y2, evts[i].evtCode);
    }
    return area;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < n; i++)
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        cout << getArea() << '\n';
    }
    return 0;
}
