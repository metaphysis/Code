// Overlapping Areas
// UVa ID: 934
// Verdict: Accepted
// Submission Date: 2018-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

int main(int argc, char *argv[])
{
    int n;
    double xx1[MAXV], yy1[MAXV], xx2[MAXV], yy2[MAXV];

    while (cin >> n)
    {
        vector<double> xs, ys;
        for (int i = 0; i < n; i++)
        {
            cin >> xx1[i] >> yy1[i];
            cin >> xx2[i] >> yy2[i];
            if (xx1[i] > xx2[i]) swap(xx1[i], xx2[i]), swap(yy1[i], yy2[i]);
            if (yy1[i] > yy2[i]) swap(yy1[i], yy2[i]);
            xs.push_back(xx1[i]); xs.push_back(xx2[i]);
            ys.push_back(yy1[i]); ys.push_back(yy2[i]);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (int i = 0; i < n; i++)
        {
            xx1[i] = lower_bound(xs.begin(), xs.end(), xx1[i]) - xs.begin();
            xx2[i] = lower_bound(xs.begin(), xs.end(), xx2[i]) - xs.begin();
            yy1[i] = lower_bound(ys.begin(), ys.end(), yy1[i]) - ys.begin();
            yy2[i] = lower_bound(ys.begin(), ys.end(), yy2[i]) - ys.begin();
        }

        int od = 0;
        int g[2 * n][2 * n] = {}; 
        for (int c = 0; c < n; c++)
            for (int i = xx1[c]; i < xx2[c]; i++)
                for (int j = yy1[c]; j < yy2[c]; j++)
                {
                    g[i][j]++;
                    od = max(od, g[i][j]);
                }

        double area = 0;
        for (int i = 0; i < 2 * n - 1; i++)
            for (int j = 0; j < 2 * n - 1; j++)
                if (g[i][j] == od)
                    area += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);

        cout << fixed << setprecision(2) << area << '\n';
    }

    return 0;
}
