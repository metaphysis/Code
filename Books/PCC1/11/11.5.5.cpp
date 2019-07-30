// Best Cow Fences
// ID: USACO 2003 March Green
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

// 从点a向点b望去，点c位于线段ab的顺时针方向。
bool cw(point &a, point &b, point &c)
{
	return cp(a, b, c) < 0;
}

// 从点a向点b望去，点c位于线段ab的逆时针方向。
bool ccw(point &a, point &b, point &c)
{
	return cp(a, b, c) >= 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, F, si, head, rear, best, Q[MAXN];
    while (cin >> N >> F)
    {
        point maxK(1, 0);
        // 初始化单调队列，将参考点放入队列。
        si = head = rear = best = 0;
        P[0] = point(0, 0), Q[rear++] = 0;
        for (int i = 1, ai; i <= N; i++)
        {
            cin >> ai;
            P[i] = point(i, si + ai);
            // 选择单调队列中的某个点，该点与P[i]构成的直线具有最大的斜率。
            while (best + 2 <= rear && Q[best] <= i - F && ccw(P[Q[best]], P[Q[best + 1]], P[i])) best++;
            // 最优决策点需要满足长度的约束。
            if (Q[best] <= i - F)
            {
                point k = point(i - Q[best], P[i].y - P[Q[best]].y);
                if (maxK.y * k.x < maxK.x * k.y) maxK = k;
            }
            // 将P[i]放入队列，保持相邻决策点连线斜率单调不降。
            // 既往的最佳决策点可能已经被删除，需要予以调整。由下凸包折线斜率的单调
            // 不降可知队列末端的决策点一定比位于左侧的决策点更优，因此直接将最优决
            // 策点的指针指向队列最末尾一个元素即可。
            while ((rear - head) >= max(F, 2) && cw(P[Q[rear - 2]], P[Q[rear - 1]], P[i]))
            {
                rear--;
                if (best >= rear) best = rear - 1;
            }
            Q[rear++] = i;
            si += ai;
        }
        cout << maxK.y << ' ' << maxK.x << '\n';
        cout << 1000 * maxK.y / maxK.x << '\n';
    }
    return 0;
}
