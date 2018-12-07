// WiFi
// UVa ID: 11516
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

int n, m;
double house[100010];

bool satisfy(double mid)
{
    int r = n - 1;
    double last = house[0] + mid;
    for (int i = 1; i < m && r >= 0; i++)
    {
        if (fabs(last - house[i]) <= mid + EPSILON) continue;
        last = house[i] + mid;
        r--;
    }
    return r >= 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++) cin >> house[i];
        sort(house, house + m);
        double low = 0, high = 1000000, mid;
        while (fabs(low - high) > EPSILON)
        {
            mid = (low + high) / 2;
            if (satisfy(mid)) high = mid;
            else low = mid;
        }
        cout << fixed << setprecision(1) << mid << '\n';
    }

    return 0;
}
