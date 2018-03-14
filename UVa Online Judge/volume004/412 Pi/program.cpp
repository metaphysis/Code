// Pi
// UVa ID: 412
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
    int t;
    while (a % b) t = a, a = b, b = t % b;
    return b;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n)
    {
        vector<int> number(n);
        for (int i = 0; i < n; i++)
            cin >> number[i];
            
        int counter = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (gcd(number[i], number[j]) == 1)
                    counter++;
                    
        if (counter == 0) cout << "No estimate for this data set." << endl;
        else
        {
            long double pi = sqrt(3.0 * n * (n - 1) / counter);
            cout << fixed << setprecision(6) << pi << endl;
        }
    }
    
	return 0;
}
