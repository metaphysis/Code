// Lowest Price in Town
// UVa ID: 10980
// Verdict: Accepted
// Submission Date: 2018-01-19
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    int cases = 0;
    while (getline(cin, line))
    {
        string P;
        int M, N, K;

        istringstream iss(line);
        iss >> P >> M;

        for (int i = P.length() - 1; i >= 0; i--)
            if (P[i] == '.')
            {
                P.erase(P.begin() + i);
                break;
            }

        int cnt[24], money[24];
        cnt[0] = 1, money[0] = stoi(P);
        
        for (int i = 1; i <= M; i++)
        {
            getline(cin, line); iss.clear(); iss.str(line);
            iss >> N >> P;
            cnt[i] = N;
            
            for (int i = P.length() - 1; i >= 0; i--)
                if (P[i] == '.')
                {
                    P.erase(P.begin() + i);
                    break;
                }
            money[i] = stoi(P); 
        }

        cout << "Case " << ++cases << ":\n";
        getline(cin, line); iss.clear(); iss.str(line);

        while (iss >> K)
        {
            int lowest[210], INF = 0x3fffffff;
            for (int i = 0; i <= 200; i++)
                lowest[i] = INF;
            lowest[0] = 0;
            
            for (int i = 0; i <= M; i++)
                for (int j = cnt[i]; j <= 200; j++)
                    lowest[j] = min(lowest[j], lowest[j - cnt[i]] + money[i]);
            
            int minPrice = INF;
            for (int k = K; k <= 200; k++)
                minPrice = min(minPrice, lowest[k]);

            cout << "Buy " << K << " for $";
            cout << minPrice / 100 << '.';
            minPrice %= 100;
            if (minPrice < 10) cout << '0';
            cout << minPrice;
            cout << '\n';
        }
    }

    return 0;
}
