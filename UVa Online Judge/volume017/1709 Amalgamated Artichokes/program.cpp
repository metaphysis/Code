// Amalgamated Artichokes
// UVa ID: 1709
// Verdict: TLE
// Submission Date: 2021-12-02
// UVa Run Time: s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define LC(x) ((x << 1) | 1)
#define RC(x) ((x + 1) << 1)

const int MAXV = 1000100;
const double INF = 1e10;

int p, a, b, c, d, n;
double st[MAXV << 2];

double inline getPrice(int k)
{
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

void build(int p, int left, int right)
{
    if (left == right) st[p] = getPrice(left + 1);
    else
    {
        int middle = (left + right) >> 1;
        build(LC(p), left, middle);
        build(RC(p), middle + 1, right);
        st[p] = min(st[LC(p)], st[RC(p)]);
    }
}

double query(int p, int left, int right, int qleft, int qright)
{
    if (right < qleft || left > qright) return INF;
    if (qleft <= left && right <= qright) return st[p];
    int middle = (left + right) >> 1;
    return min(query(LC(p), left, middle, qleft, qright),
        query(RC(p), middle + 1, right, qleft, qright));
}

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> p >> a >> b >> c >> d >> n)
    {
        build(0, 0, n - 1);
        double maxDecline = 0;
        for (int i = 0; i < n - 1; i++)
            maxDecline = max(maxDecline, getPrice(i + 1) - query(0, 0, n - 1, i + 1, n - 1));
        cout << fixed << setprecision(8) << maxDecline << '\n';
    }
    return 0;
}
