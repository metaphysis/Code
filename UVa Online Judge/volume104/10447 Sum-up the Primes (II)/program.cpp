// Sum-up the Primes (II)
// UVa ID: 10447
// Verdict:
// Submission Date:
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[301] = {}, cnt = 0;
int Q, N, T, B;
int dpWith2[801][13][256], dpWithout2[801][13][256];
int sq1[801][13][13], sq2[801][13][13];
vector<int> primesWith2, primesWithout2;

bool cmp(int a, int b)
{
    return to_string(a) < to_string(b);
}

void DP(vector<int> &ps, int dp[801][13][256], int sq[801][13][13])
{
    sort(ps.begin(), ps.end(), cmp);
    //sort(primesWithout2.begin(), primesWithout2.end(), cmp);

    memset(dp, 0, 801 * 13 * 256 * sizeof(int));
    //memset(dpWithout2, 0, sizeof(dpWithout2));

    memset(sq, 0, 801 * 13 * 13 * sizeof(int));
    //memset(sq2, 0, sizeof(sq2));

    for (int i = 0; i < ps.size(); i++)
    {
        if (i && ps[i] == ps[i - 1]) continue;
        sq[ps[i]][1][0] = 1;
        sq[ps[i]][1][1] = ps[i];
        dp[ps[i]][1][i] = 1;
    }

    for (int i = 2; i <= 12; i++)
        for (int j = 0; j <= 800; j++)
        {
            if (!sq[j][i - 1][0]) continue;
            for (int k = 0; k < ps.size(); k++)
            {
                if (dp[j][i - 1][k]) continue;
                if (j + ps[k] > 800) continue;
                
                // less?
                bool updated = true;
                if (sq[j + ps[k]][i][0])
                {
                    int resultOfCompare = 0;
                    for (int l = 1; l < i; l++)
                    {
                        if (sq[j + ps[k]][i][l] != sq[j][i - 1][l])
                        {
                            if (to_string(sq[j + ps[k]][i][l]) > to_string(sq[j][i - 1][l]))
                                resultOfCompare = 1;
                            else
                                resultOfCompare = -1;
                            break;
                        }
                    }
                    if (resultOfCompare == 0)
                    {
                        if (sq[j + ps[k]][i][i] != ps[k])
                        {
                            if (to_string(sq[j + ps[k]][i][i]) > to_string(ps[k]))
                                resultOfCompare = 1;
                            else
                                resultOfCompare = -1;
                        }
                    }
                    if (resultOfCompare <= 0)
                        updated = false;
                }
                if (!updated) continue;

                //if (j + primesWith2[k] == 152)
                //{
                //    for (int l = 1; l < i; l++)
                //        cout << sq1[j][i - 1][l] << '+';
                //    cout << primesWith2[k] << '\n';
                //}

                sq[j + ps[k]][i][0] = 1;
                memcpy(dp[j + ps[k]][i], dp[j][i - 1], 256 * sizeof(int));
                dp[j + ps[k]][i][k] = 1;
                memcpy(sq[j + ps[k]][i], sq[j][i - 1], 13 * sizeof(int));
                sq[j + ps[k]][i][i] = ps[k];
                sort(sq[j + ps[k]][i] + 1, sq[j + ps[k]][i] + i + 1, cmp);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i <= 300; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }
    
    int blocks;
    cin >> blocks;
    for (int bs = 1; bs <= blocks; bs++)
    {
        primesWith2.clear();
        primesWithout2.clear();

        int f;
        cout << "Block " << bs << ":\n";
        for (int i = 1; i <= 61; i++)
        {
            cin >> f;
            for (int j = 1; j <= f; j++)
            {
                primesWith2.push_back(primes[i]);
                primesWithout2.push_back(primes[i]);
            }
        }

        primesWith2.push_back(2);

        DP(primesWith2, dpWith2, sq1);
        DP(primesWithout2, dpWithout2, sq2);

        cin >> Q;
        for (int q = 1; q <= Q; q++)
        {
            cin >> N >> T >> B;

            cout << "Query " << q << ":\n";

            if (B)
            {
                if (!sq1[N][T][0]) cout << "No Solution.\n";
                else
                {
                    for (int i = 1; i <= T; i++)
                    {
                        if (i > 1) cout << '+';
                        cout << sq1[N][T][i];
                    }
                    cout << '\n';
                }
            }
            else
            {
                if (!sq2[N][T][0]) cout << "No Solution.\n";
                else
                {
                    for (int i = 1; i <= T; i++)
                    {
                        if (i > 1) cout << '+';
                        cout << sq2[N][T][i];
                    }
                    cout << '\n';
                }
            }
        }
        cout << '\n';
    }

    return 0;
}
