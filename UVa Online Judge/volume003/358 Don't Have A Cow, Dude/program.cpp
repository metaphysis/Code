// Don't Have A Cow, Dude
// UVa ID: 358
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

const double PI = 2.0 * acos(0.0);

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases;
    string R, P;
    
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        cin >> R >> P;
        
        double r = stod(R), p = stod(P);
        double low = 0.0, up = 2.0 * r;
        
        int iterations = 0;
        while (fabs(low - up) >= 1e-7 && iterations++ <= 40)
        {
            double middle = (low + up) / 2.0;
            double a1 = acos((2.0 * r * r - middle * middle) / (2.0 * r * r));
            double a2 = acos(middle / (2.0 * r));
            double next_p = (r * r * a1 + middle * middle * a2 - r * r * sin(a1)) / (PI * r * r);
            
            if (next_p < p)
                low = middle;
            else
                up = middle;
        }
        
        cout << "R = " << R;
        cout << ", P = " << fixed << setprecision(2) << p;
        cout << ", Rope = " << fixed << setprecision(2) << low << endl;
    }
    
	return 0;
}
