// An Angular Puzzle
// UVa ID: 12301
// Verdict: Accepted
// Submission Date: 2018-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e)
    {
        if (a == 0) break;
        if (a + b + c + d + e != 180)
        {
            cout << "Impossible" << '\n';
            continue;
        }
        
        double angleADB = (180 - b - c - e) * PI / 180;
        double AD = sin(e * PI / 180) / sin(angleADB);
        double angleAEB = (180 - c - d - e) * PI / 180;
        double AE = sin((d + e) * PI / 180) / sin(angleAEB);
        double DE = sqrt(AD * AD + AE * AE - 2 * AD * AE * cos(b * PI / 180));
        double angleDEA = acos((AE - AD * cos(b * PI / 180)) / DE);
        cout << fixed << setprecision(2) << (angleDEA * 180 / PI) << '\n'; 
    }

    return 0;
}
