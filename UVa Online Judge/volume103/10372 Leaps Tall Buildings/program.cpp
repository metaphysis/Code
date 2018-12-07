// Leaps Tall Buildings
// UVa ID: 10372
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double MAXA = acos(0), EPSILON = 1e-7, G = 9.8;

int n, C;
double dn[256], hn[256], W, xx, yy;

bool conflict(double angle)
{
    double vx = sqrt(G * W / (2 * tan(angle)));
    double vy = sqrt(G * W * tan(angle) / 2);
    for (int i = 0; i < C; i++)
    {
        double t = dn[i] / vx;
        double vh = vy * t - 0.5 * G * t * t;
        if (vh + EPSILON < hn[i]) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        W = 0, C = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> yy >> xx;
            dn[C] = W, hn[C] = yy;
            C++;
            W += xx;
            dn[C] = W, hn[C] = yy;
            C++;
        }
        double lowa = 0, higha = MAXA, mida;
        while (fabs(higha - lowa) > EPSILON)
        {
            mida = (lowa + higha) / 2;
            if (conflict(mida)) lowa = mida;
            else higha = mida;
        }
        double v = sqrt((G * W) / (2 * sin(lowa) * cos(lowa)));
        cout << fixed << setprecision(2) << (lowa * 90 / MAXA) << ' ' << v << '\n';
    }

    return 0;
}
