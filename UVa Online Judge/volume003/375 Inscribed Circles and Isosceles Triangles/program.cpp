// Inscribed Circles and Isosceles Triangles
// UVa ID: 375
// Verdict: Accepted
// Submission Date: 2016-07-03
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0.0);

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    double n, B, H, sumOfR, r;
    cin >> n;
    
    cout << fixed << setprecision(6);
    
    for (int i = 1; i <= n; i++)
    {
        cin >> B >> H;
        
        if (i > 1) cout << endl;
        
        sumOfR = 0.0, r = H * B / (B + sqrt(4 * H * H + B * B));
        while (r >= 0.000001)
        {
            sumOfR += r;
            H -= 2 * r;
            r *= H / (H + 2 * r);
        }
    
        cout << right << setw(13) << (2.0 * PI * sumOfR) << endl;
    }
    
	return 0;
}
