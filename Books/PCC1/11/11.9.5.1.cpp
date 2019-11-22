// USACO 2003 March Green - Best Cow Fences
// POJ ID: 2018
// Verdict: Accepted
// Submission Date: 2019-07-31
// UVa Run Time: 0.313s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <stdio.h>

using namespace std;

const int MAXN = 100010;
const double EPSILON = 1e-6;

int N, F;
double si[MAXN], ai[MAXN];

bool isWorked(double middle)
{
    double now, best;
    best = si[F - 1] - middle * (F - 1);
    for (int i = F; i <= N; i++)
    {
        now = si[i] - si[i - F] - middle * F;
        best = best + ai[i] - middle;
        if (now > best) best = now;
        if (best >= -EPSILON) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    while (scanf("%d%d", &N, &F) != EOF)
    {
        double low = 2000, high = 0;
        ai[0] = si[0] = 0;
        for (int i = 1; i <= N; i++)
        {
            scanf("%lf", &ai[i]);
            if (ai[i] > high) high = ai[i];
            if (ai[i] < low) low = ai[i];
            si[i] = si[i - 1] + ai[i];
        }
        while (high - low >= EPSILON)
        {
            double middle = (low + high) / 2;
            if (isWorked(middle)) low = middle;
            else high = middle;
        }
        printf("%d\n", (int)(high * 1000));
    }

    return 0;
}
