// Polynomial Roots
// UVa ID: 930
// Verdict: Accepted
// Submission Date: 2017-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int degree, n;
        double coefficients[100], roots[100];
        
        cin >> n;
        for (int i = 0; i <= n; i++)
            cin >> coefficients[i];
            
        n -= 2;
        for (int i = 0; i < n; i++)
            cin >> roots[i];

        degree = n + 2;
        
        int idx = 0;
        while (degree > 2)
        {
            for (int j = 1; j < degree; j++)
                coefficients[j] += coefficients[j - 1] * roots[idx];
            
            degree--;
            idx++;
        }
        
        double root1 = sqrt(coefficients[1] * coefficients[1] - 4.0 * coefficients[0] * coefficients[2]);
        double root2 = (-coefficients[1] - root1) / (2.0 * coefficients[0]);
        double root3 = (-coefficients[1] + root1) / (2.0 * coefficients[0]);
        
        if (root2 + epsilon < root3) swap(root2, root3);
        cout << fixed << setprecision(1) << root2 << '\n';
        cout << fixed << setprecision(1) << root3 << '\n';
    }
    
    return 0;
}
