// Sum-up the Primes (II)
// UVa ID: 10447
// Verdict:
// Submission Date:
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int Q, N, T, F;
int dp1[256][810][16], dp2[256][810][16];
vector<int> available1, available2;

bool cmp(int a, int b)
{
    return to_string(a) > to_string(b);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[301] = {}, cnt = 0;
    for (int i = 2; i <= 300; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }

    int B;
    cin >> B;
    for (int b = 1; b <= B; b++)
    {
        available1.clear();
        available2.clear();

        cout << "Block " << b << ":\n";
        for (int i = 1, f; i <= 61; i++)
        {
            cin >> f;
            for (int j = 1; j <= f; j++)
            {
                available1.push_back(primes[i]);
                available2.push_back(primes[i]);
            }
        }

        sort(available1.begin(), available1.end(), cmp);
        available1.insert(available1.begin(), 0);

        memset(dp1, 0, sizeof(dp1));
        dp1[0][0][0] = 1;
        for (int i = 1; i < available1.size(); i++)
            for (int j = 0; j <= 800; j++)
                for (int k = 0; k <= 12; k++)
                {
                    dp1[i][j][k] |= dp1[i - 1][j][k];
                    if (j < available1[i] || !k) continue;
                    dp1[i][j][k] |= dp1[i - 1][j - available1[i]][k - 1];
                }
        
        available2.push_back(2);
        sort(available2.begin(), available2.end(), cmp);
        available2.insert(available2.begin(), 0);

        memset(dp2, 0, sizeof(dp2));
        dp2[0][0][0] = 1;
        for (int i = 1; i < available2.size(); i++)
            for (int j = 0; j <= 800; j++)
                for (int k = 0; k <= 12; k++)
                {
                    dp2[i][j][k] |= dp2[i - 1][j][k];
                    if (j < available2[i] || !k) continue;
                    dp2[i][j][k] |= dp2[i - 1][j - available2[i]][k - 1];
                }

        cin >> Q;
        for (int q = 1; q <= Q; q++)
        {
            cin >> N >> T >> F;

            cout << "Query " << q << ":\n";
            if (!F && (N % 2 != T % 2))
            {
                cout << "No Solution.\n";
                continue;
            }

            if (!F)
            {
                if(!dp1[available1.size() - 1][N][T]) cout << "No Solution.\n";
		        else
		        {
			        for(int x = available1.size() - 1, y = N, z = T; y && x && z; x--)
				        if(dp1[x][y][z] && y - available1[x] >= 0 && dp1[x - 1][y - available1[x]][z - 1])
				        {
					        y -= available1[x];
					        cout << available1[x] << "+\n"[!y];
					        z--;
				        }
		        }
		    }
		    else
		    {
		        if(!dp2[available2.size() - 1][N][T]) cout << "No Solution.\n";
		        else
		        {
			        for(int x = available2.size() - 1, y = N, z = T; y && x && z; x--)
				        if(dp2[x][y][z] && y - available2[x] >= 0 && dp2[x - 1][y - available2[x]][z - 1])
				        {
					        y -= available2[x];
					        cout << available2[x] << "+\n"[!y];
					        z--;
				        }
		        }
		    }
        }
        cout << '\n';
    }

    return 0;
}
