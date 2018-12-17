// Divide the Land
// UVa ID: 11648
// Verdict: Accepted
// Submission Date: 2018-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        double AB, CD, AD, BC;
        cin >> AB >> CD >> AD >> BC;
        double AB_CD = AB - CD;
        double DAB = acos((AD * AD + AB_CD * AB_CD - BC * BC) / (2 * AD * AB_CD));
        double CBA = acos((BC * BC + AB_CD * AB_CD - AD * AD) / (2 * BC * AB_CD));
        double AREA = (AB + CD) * AD * sin(DAB) / 2;
        double low = 0, high = AD, AE;
        int cnt = 0;
        while (fabs(high - low) > 1e-8 && cnt++ < 60)
        {
            AE = (low + high) / 2;
            double H = AE * sin(DAB);
            double EF = AB - AE * cos(DAB) - H / tan(CBA);
            double AREA2 = (AB + EF) * H / 2;
            if (AREA2 * 2 >= AREA) high = AE;
            else low = AE;
        }
        double BF = BC * AE / AD;
        cout << "Land #" << cs << ": ";
        cout << fixed << setprecision(6) << AE << ' ' << BF << '\n';
    }

    return 0;
}
