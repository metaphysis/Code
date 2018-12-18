// In-Circle
// UVa ID: 11524
// Verdict: Accepted
// Submission Date: 2018-12-18
// UVa Run Time: 0.280s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double r, m1, n1, m2, n2, m3, n3;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> r >> m1 >> n1 >> m2 >> n2 >> m3 >> n3;
        double low = 0, high = 1e10, BC, CA, AB, P, R;
        int cnt = 0;
        while (fabs(high - low) > 1e-7 && cnt++ < 60)
        {
            BC = (low + high) / 2;
            CA = (BC * n2 / (m2 + n2)) * (m3 + n3) / m3;
            AB = (BC * m2 / (m2 + n2)) * (m1 + n1) / n1;
            P = (BC + CA + AB) / 2;
            R = sqrt((P - BC) * (P - CA) * (P - AB) / P);
            if (R >= r) high = BC;
            else low = BC;
        }
        cout << fixed << setprecision(4) << sqrt(P * (P - BC) * (P - CA) * (P - AB)) << '\n';
    }

    return 0;
}
