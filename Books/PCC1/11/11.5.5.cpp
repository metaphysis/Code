// USACO 2003 March Green - Best Cow Fences
// POJ ID: 2018
// Verdict: Accepted
// Submission Date: 2019-07-31
// UVa Run Time: 0.688s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

const int MAXN = 100010;

struct point {
    long long x, y;
    point (long long x = 0, long long y = 0): x(x), y(y) {}
} P[MAXN];

// 叉积。
long long cp(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 如果叉积小于0，则从点a向点b望去，点c位于线段ab的右侧，即两条连续线段ab和bc构成右转。
bool cw(point &a, point &b, point &c)
{
	return cp(a, b, c) < 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, F, ai, si, head, rear, best, Q[MAXN];
    while (cin >> N >> F)
    {
        point maxK(1, 0);
        // 初始化单调队列，将参考点放入队列。
        si = head = rear = best = 0;
        P[0] = point(0, 0), Q[rear++] = 0;
        for (int i = 1; i <= N; i++)
        {
            cin >> ai;
            si += ai;
            P[i] = point(i, si);
            // 选择单调队列中的某个点，该点与P[i]构成的直线具有最大的斜率。
            if (best >= rear) best = rear - 1;
            while (best && i - Q[best] < F) best--;
            while (best && i - Q[best] >= F && cw(P[Q[best - 1]], P[Q[best]], P[i])) best--;
            while (best + 2 <= rear && i - Q[best + 1] >= F && !cw(P[Q[best]], P[Q[best + 1]], P[i])) best++;
            // 最优决策点需要满足长度的约束。
            if (i - Q[best] >= F)
            {
                point k = point(i - Q[best], P[i].y - P[Q[best]].y);
                if (maxK.y * k.x < maxK.x * k.y) maxK = k;
            }
            // 将符合长度约束的决策点送入队列并求下凸包。
            while ((i + 1) - Q[rear - 1] > F)
            {
                int j = Q[rear - 1] + 1;
                while (rear - head >= 2 && cw(P[Q[rear - 2]], P[Q[rear - 1]], P[j])) rear--;
                Q[rear++] = j;
            }
        }
        cout << 1000 * maxK.y / maxK.x << '\n';
    }
    return 0;
}
