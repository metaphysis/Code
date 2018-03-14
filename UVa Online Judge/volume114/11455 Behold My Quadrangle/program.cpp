// Behold My Quadrangle
// UVa ID: 11455
// Verdict: Accepted
// Submission Date: 11455
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long sides[4];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 4; i++) cin >> sides[i];
        sort(sides, sides + 4);
        
        if (sides[0] == sides[3]) cout << "square\n";
        else
        {
            if (sides[0] == sides[1] && sides[2] == sides[3]) cout << "rectangle\n";
            else
            {
                int flag = 0;
                do
                {
                    long long minL1 = abs(sides[2] - sides[3]);
                    long long maxL1 = sides[2] + sides[3];
                    
                    long long minL2 = abs(sides[0] - sides[1]);
                    long long maxL2 = sides[0] + sides[1];
                    
                    if (minL2 >= minL1 && minL2 < maxL1 || minL2 >= minL1 && minL2 < maxL1)
                    {
                        flag = 1;
                        break;
                    }
                } while (next_permutation(sides, sides + 4));
                if (flag) cout << "quadrangle\n";
                else cout << "banana\n";
            }
        }
    }

    return 0;
}
