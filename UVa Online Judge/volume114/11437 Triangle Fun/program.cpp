// Triangle Fun
// UVa ID: 11437
// Verdict: Accepted
// Submission Date: 2017-12-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

double getArea(double a, double b, double c, double A, double B, double C)
{
    double BD = a / 3.0;
    double AD = sqrt(c * c + BD * BD - 2.0 * c * BD * cos(B));
    double PDB = acos((AD * AD + BD * BD - c * c) / (2.0 * AD * BD));
    
    double CE = b / 3.0;
    double BE = sqrt(a * a + CE * CE - 2.0 * a * CE * cos(C));
    double BEC = acos((BE * BE + CE * CE - a * a) / (2.0 * BE * CE));
    double PBD = PI - C - BEC;
    double BPD = PI - PDB - PBD;
    
    double BP = BD * sin(PDB) / sin(BPD);
    double PD = BD * sin(PBD) / sin(BPD);
    
    double p = (BD + BP + PD) / 2;
    return sqrt(p * (p - BD) * (p - BP) * (p - PD));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(0);

    int cases;
    cin >> cases;
    
    double xa, ya, xb, yb, xc, yc;
    double a, b, c, A, B, C;

    for (int k = 1; k <= cases; k++)
    {
        cin >> xa >> ya >> xb >> yb >> xc >> yc;
        a = sqrt(pow(xb - xc, 2) + pow(yb - yc, 2));
        b = sqrt(pow(xc - xa, 2) + pow(yc - ya, 2));
        c = sqrt(pow(xa - xb, 2) + pow(ya - yb, 2));
        A = acos((b * b + c * c - a * a) / (2.0 * b * c));
        B = acos((a * a + c * c - b * b) / (2.0 * a * c));
        C = PI - A - B;
        
        double area1 = getArea(a, b, c, A, B, C);       
        double area2 = getArea(b, c, a, B, C, A);
        double area3 = getArea(c, a, b, C, A, B);
        
        cout << (area1 + area2 + area3) << '\n';
    }

    return 0;
}
