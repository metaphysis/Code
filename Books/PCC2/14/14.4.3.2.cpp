#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, ADD = 1, DELETE = -1;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

struct rectangle { int x1, y1, x2, y2; } rects[MAXN];
struct event {
    int x, y1, y2, evtCode;
    bool operator<(const event &e) const { return x < e.x; }
} evts[MAXN * 2];

struct node { int cnt, leftCovered, rightCovered, part, h; } st[4 * MAXN] = {};

int n, id[MAXN *2];

void build(int p, int left, int right)
{
    if (left != right) {
        int middle = (left + right) >> 1;
        build(LC(p), left, middle);
        build(RC(p), middle + 1, right);
    }
    st[p].cnt = st[p].leftCovered = st[p].rightCovered = st[p].part = 0;
    st[p].h = 0;
}

void pushUp(int p, int left, int right)
{
    if (st[p].cnt) {
        st[p].part = st[p].leftCovered = st[p].rightCovered = 1;
        st[p].h = id[right + 1] - id[left];
    } else {
        if (left == right) {
            st[p].part = st[p].leftCovered = st[p].rightCovered = 0;
            st[p].h = 0;
        } else {
            st[p].part = st[LC(p)].part + st[RC(p)].part;
            st[p].part -= (st[LC(p)].rightCovered & st[RC(p)].leftCovered);
            st[p].leftCovered = st[LC(p)].leftCovered;
            st[p].rightCovered = st[RC(p)].rightCovered;
            st[p].h = st[LC(p)].h + st[RC(p)].h;
        }
    }
}

void update(int p, int left, int right, int ul, int ur, int value)
{    
    if (right < ul || left > ur) return;
    if (ul <= left && right <= ur) st[p].cnt += value;
    else {
        int middle = (left + right) >> 1;
        if (middle >= ul) update(LC(p), left, middle, ul, ur, value);
        if (middle + 1 <= ur) update(RC(p), middle + 1, right, ul, ur, value);
    }
    pushUp(p, left, right);
}

int getLength()
{
    for (int i = 0; i < n; i++) id[i] = rects[i].y1, id[i + n] = rects[i].y2;
    sort(id, id + 2 * n);
    for (int i = 0; i < n; i++) {
        evts[i].evtCode = ADD, evts[i].x = rects[i].x1;
        evts[i + n].evtCode = DELETE, evts[i + n].x = rects[i].x2;
        int ty1 = lower_bound(id, id + 2 * n, rects[i].y1) - id;
        int ty2 = lower_bound(id, id + 2 * n, rects[i].y2) - id;
        evts[i].y1 = evts[i + n].y1 = ty1;
        evts[i].y2 = evts[i + n].y2 = ty2;
    }
    sort(evts, evts + 2 * n);
    int length = 0, lastH = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i && evts[i].x > evts[i - 1].x)
            length += 2 * st[0].part * (evts[i].x - evts[i - 1].x);
        update(0, 0, 2 * n - 1, evts[i].y1, evts[i].y2 - 1, evts[i].evtCode);
        length += abs(st[0].h - lastH);
        lastH = st[0].h;
    }
    return length;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n, n > 0) {
        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < n; i++)
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        int length = getLength();
        cout << length << '\n';
    }
    return 0;
}
