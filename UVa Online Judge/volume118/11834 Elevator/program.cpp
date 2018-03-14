// Elevator
// UVa ID: 11834
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double L, C, R1, R2;
    
    while (cin >> L >> C >> R1 >> R2)
    {
        if (L == 0) break;
        
        if (L < C) swap(L, C);
        if (R1 < R2) swap(R1, R2);

        if (2 * R1 > C)
        {
            cout << "N\n";
            continue;
        }
        
        double W = sqrt(pow(R1 + R2, 2) - pow(R1 - R2, 2));
        double rightMost = max(2 * R1, R1 + W + R2);

        if (rightMost <= L)
        {
            cout << "S\n";
            continue;
        }
        
        W = sqrt(pow(R1 + R2, 2) - pow(C - R1 - R2, 2));
        rightMost = max(2 * R1, R1 + W + R2);
        if (rightMost <= L)
        {
            cout << "S\n";
            continue;
        }

        cout << "N\n";
    }

    return 0;
}
