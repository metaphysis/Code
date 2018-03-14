// The Wedding
// UVa ID: 10662
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int t, r, h;
    int tp[20], rp[20], hp[20];
    int tr[20][20], rh[20][20], ht[20][20];
    
    while (cin >> t >> r >> h)
    {
        for (int i = 0; i < t; i++)
        {
            cin >> tp[i];
            for (int j = 0; j < r; j++)
                cin >> tr[i][j];
        }
        
        for (int i = 0; i < r; i++)
        {
            cin >> rp[i];
            for (int j = 0; j < h; j++)
                cin >> rh[i][j];
        }
        
        for (int i = 0; i < h; i++)
        {
            cin >> hp[i];
            for (int j = 0; j < t; j++)
                cin >> ht[i][j];
        }
        
        int st, sr, sh, price = 0x3fffffff;
        for (int i = 0; i < t; i++)
            for (int j = 0; j < r; j++)
                for (int k = 0; k < h; k++)
                    if (tr[i][j] + rh[j][k] + ht[k][i] == 0)
                    {
                        if (tp[i] + rp[j] + hp[k] < price)
                        {
                            price = tp[i] + rp[j] + hp[k];
                            st = i, sr = j, sh = k;
                        }
                    }
                    
        if (price < 0x3fffffff)
            cout << st << ' ' << sr << ' ' << sh << ':' << price << '\n';
        else
            cout << "Don't get married!\n";
    }
    
    return 0;
}
