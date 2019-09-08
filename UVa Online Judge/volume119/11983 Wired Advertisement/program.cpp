// Wired Advertisement
// UVa ID: 11983
// Verdict: Accepted
// Submission Date: 2019-09-03
// UVa Run Time: 0.350s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60010, ADD = 1, DELETE = -1;

#define LCHILD(x) (((x) << 1) | 1)
#define RCHILD(x) (((x) + 1) << 1)

struct rectangle { int x1, y1, x2, y2; } rects[MAXN];
struct event {
    int x, y1, y2, evtCode;
    bool operator<(const event &e) const { return x < e.x; }
} evts[MAXN * 2];
struct node { int cnt, height[11]; } st[4 * MAXN] = {};

int N, K, id[MAXN * 2];

void pushUp(int p, int left, int right)
{
    memset(st[p].height, 0, sizeof(st[p].height));
    if (st[p].cnt >= K) st[p].height[K] = id[right + 1] - id[left];
    else if (left == right)
        st[p].height[st[p].cnt] = id[right + 1] - id[left];
    else {
        for (int i = st[p].cnt; i < K; i++)
            st[p].height[i] += st[LCHILD(p)].height[i - st[p].cnt] + st[RCHILD(p)].height[i - st[p].cnt];
        for (int i = K - st[p].cnt; i <= K; i++)
            st[p].height[K] += st[LCHILD(p)].height[i] + st[RCHILD(p)].height[i];
    }
}

void build(int p, int left, int right)
{
    if (left != right) {
        int middle = (left + right) >> 1;
        build(LCHILD(p), left, middle);
        build(RCHILD(p), middle + 1, right);
    }
    st[p].cnt = 0;
    memset(st[p].height, 0, sizeof(st[p].height));
    st[p].height[0] = id[right + 1] - id[left];
}

void update(int p, int left, int right, int ul, int ur, int value)
{
    if (right < ul || left > ur) return;
    if (ul <= left && right <= ur) st[p].cnt += value;
    else {
        int middle = (left + right) >> 1;
        if (middle >= ul) update(LCHILD(p), left, middle, ul, ur, value);
        if (middle + 1 <= ur) update(RCHILD(p), middle + 1, right, ul, ur, value);
    }
    pushUp(p, left, right);
}

long long getArea()
{
    for (int i = 0; i < N; i++) id[i] = rects[i].y1, id[i + N] = rects[i].y2;
    sort(id, id + 2 * N);
    build(0, 0, 2 * N - 1);
    for (int i = 0; i < N; i++) {
        evts[i].evtCode = ADD, evts[i].x = rects[i].x1;
        evts[i + N].evtCode = DELETE, evts[i + N].x = rects[i].x2;
        evts[i].y1 = evts[i + N].y1 = lower_bound(id, id + 2 * N, rects[i].y1) - id;
        evts[i].y2 = evts[i + N].y2 = lower_bound(id, id + 2 * N, rects[i].y2) - id;
    }
    sort(evts, evts + 2 * N);
    long long area = 0;
    for (int i = 0; i < 2 * N; i++) {
        if (i && evts[i].x > evts[i - 1].x)
            area += (long long)(evts[i].x - evts[i - 1].x) * st[0].height[K];
        update(0, 0, 2 * N - 1, evts[i].y1, evts[i].y2 - 1, evts[i].evtCode);
    }
    return area;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N >> K;
        for (int i = 0; i < N; i++)
        {
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
            rects[i].x2 += 1, rects[i].y2 += 1;
        }
        cout << getArea() << '\n';
    }
    return 0;
}
