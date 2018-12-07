// Leaps Tall Buildings
// UVa ID: 10372
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0), EPSILON = 1e-7, G = 9.8;

int n, C;
double dn[256], hn[256], W, xx, yy;

bool canFly(double angle)
{
    double H = tan(angle) * W / 4;
    double V = sqrt((2 * G * H) / (sin(angle) * sin(angle)));
    double vx = V * cos(angle), vy = V * sin(angle);
    for (int i = 0; i < C; i++)
    {
        double t = dn[i] / vx;
        double vh = vy * t - 0.5 * G * t * t;
        if (vh + EPSILON < hn[i]) return false;
    }
    return true;
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
        double lowa = 0, higha = 90, mida, answer;
        while (fabs(higha - lowa) > EPSILON)
        {
            mida = lowa + (higha - lowa) / 2;
            if (canFly(mida * PI / 180.0))
                answer = higha = mida;
            else
                lowa = mida;
        }
        double h = (tan(answer * PI / 180) * W) / 4;
        double v = sqrt((2 * G * h) / (sin(answer * PI / 180) * sin(answer * PI / 180)));
        cout << fixed << setprecision(2) << answer << ' ';
        cout << fixed << setprecision(2) << v << '\n';
    }

    return 0;
}
