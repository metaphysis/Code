// Meeting with Aliens
// UVa ID: 10570
// Verdict: Accepted
// Submission Date: 2022-01-19
// UVa Run Time: 0.050s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
int positionOfNumber[510], numberAtPosition[510];
int pon[510], nap[510];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        for (int i = 0, j; i < n; i++)
        {
            cin >> j;
            j--;
            positionOfNumber[j] = i;
            numberAtPosition[i] = j;
        }
        
        int best = 0x3f3f3f3f;
        for (int i = 0; i < n; i++)
        {
            int op = 0;
            memcpy(pon, positionOfNumber, sizeof positionOfNumber);
            memcpy(nap, numberAtPosition, sizeof numberAtPosition);
            for (int j = 0; j < n; j++)
            {
                if (nap[(i + j) % n] != j)
                {
                    op++;
                    pon[nap[(i + j) % n]] = pon[j];
                    nap[pon[j]] = nap[(i + j) % n]; 
                }
                if (op > best) break;
            }
            best = min(best, op);
            op = 0;
            memcpy(pon, positionOfNumber, sizeof positionOfNumber);
            memcpy(nap, numberAtPosition, sizeof numberAtPosition);
            for (int j = 0; j < n; j++)
            {
                if (nap[(i - j + n) % n] != j)
                {
                    op++;
                    pon[nap[(i - j + n) % n]] = pon[j];
                    nap[pon[j]] = nap[(i - j + n) % n]; 
                }
                if (op > best) break;
            }
            best = min(best, op);
        }
        cout << best << '\n';
    }
    
    return 0;
}
