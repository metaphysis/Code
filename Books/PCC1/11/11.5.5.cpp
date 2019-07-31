// USACO 2003 March Green - Best Cow Fences
// POJ ID: 2018
// Verdict: Accepted
// Submission Date: 2019-07-31
// UVa Run Time: 0.644s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

const int MAXN = 100010;

struct point { long long x, y; } P[MAXN];

// 叉积。
long long cp(point &a, point &b, point &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 如果叉积小于0，则从点a向点b望去，点c位于线段ab的右侧，即两条连续线段ab和bc构成右转。
bool cw(int a, int b, int c)
{
    return cp(P[a], P[b], P[c]) < 0;
}

// 如果叉积大于0，则从点a向点b望去，点c位于线段ab的左侧，即两条连续线段ab和bc构成左转。
bool ccw(int a, int b, int c)
{
    return cp(P[a], P[b], P[c]) > 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    point maxK, k;
    int N, F, ai, si, head, rear, Q[MAXN];
    P[0].x = P[0].y = 0;
    while (cin >> N >> F) {
        // 读入数据。
        si = 0;
        for (int i = 1; i <= N; i++) {
            cin >> ai;
            si += ai;
            P[i].x = i, P[i].y = si;
        }
        // 根据单调性确定最优决策点。
        maxK.x = 1, maxK.y = 0;
        head = 0, rear = 0;
        for (int i = 0; i + F <= N; i++) {
            while (head + 2 <= rear && cw(Q[rear - 2], Q[rear - 1], i)) rear--;
            Q[rear++] = i;
            while (head + 2 <= rear && ccw(Q[head], Q[head + 1], i + F)) head++;
            k.x = i + F - Q[head], k.y = P[i + F].y - P[Q[head]].y;
            if (maxK.y * k.x < maxK.x * k.y) maxK = k;
        }
        cout << 1000 * maxK.y / maxK.x << '\n';
    }
    return 0;
}
