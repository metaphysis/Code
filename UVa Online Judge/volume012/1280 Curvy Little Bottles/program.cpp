// Curvy Little Bottles
// UVa ID: 1280
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0), EPSILON = 1e-7;

int n;
double coefficient[24], updated[24], xlow, xhigh, increment;

double getVolume(double x)
{
    double v = 0;
    for (int i = 0; i <= n + n; i++)
        v += updated[i] * pow(x, i + 1);
    return v;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n)
    {
        for (int i = 0; i <= n; i++) cin >> coefficient[i];
        cin >> xlow >> xhigh >> increment;
        for (int i = 0; i < 24; i++) updated[i] = 0.0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++) updated[i + j] += coefficient[i] * coefficient[j];
        for (int i = 0; i <= n + n; i++) updated[i] /= (i + 1.0);
        double T = PI * (getVolume(xhigh) - getVolume(xlow));
        cout << "Case " << ++cases << ": " << fixed << setprecision(2) << T << '\n';
        if (T < increment) cout << "insufficient volume\n";
        else
        {
            double marked = increment;
            for (int i = 0; i < 8 && marked < T; i++)
            {
                double lowH = xlow, highH = xhigh, H, V;
                while (fabs(highH - lowH) > EPSILON)
                {
                    H = (lowH + highH) / 2.0;
                    V = PI * (getVolume(H) - getVolume(xlow));
                    if (V > marked) highH = H;
                    else lowH = H;
                }
                if (i) cout << ' ';
                cout << fixed << setprecision(2) << (H - xlow);
                marked += increment;
            }
            cout << '\n';
        }
    }

    return 0;
}
