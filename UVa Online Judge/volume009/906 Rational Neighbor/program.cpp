// Rational Neighbor
// UVa ID: 906
// Verdict: Accepted
// Submission Date: 2017-03-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long a, b, c, d, e, f;
    string epsilon;
    
    while (cin >> a >> b >> epsilon)
    {
        while (epsilon.back() == '0') epsilon.erase(epsilon.end() - 1);
        while (epsilon.front() != '.') epsilon.erase(epsilon.begin());
        if (epsilon.front() == '.') epsilon.erase(epsilon.begin());
        
        e = 0, f = 1;
        for (int i = 0; i < epsilon.length(); i++)
            e = e * 10 + epsilon[i] - '0', f *= 10;

        for (d = 1; ; d++)
        {
            c = a * d / b;
            while (a * d >= b * c) c++;
            if ((b * c - a * d) * f - b * d * e <= 0)
            {
                cout << c << ' ' << d << '\n';
                break;
            }
        }
    }
    
    return 0;
}
