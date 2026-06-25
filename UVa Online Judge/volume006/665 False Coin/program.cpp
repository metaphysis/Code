// False coin
// UVa ID: 665
// Verdict: Accepted
// Submission Date: 2017-05-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, N, K, Pi;
    unordered_set<int> leftPan[128], rightPan[128];
    char result[128];
    
    cin >> M;
    for (int c = 1; c <= M; c++)
    {
        if (c > 1) cout << '\n';
        
        cin >> N >> K;
        
        int identifiers;
        for (int i = 1; i <= K; i++)
        {
            leftPan[i].clear(), rightPan[i].clear();

            cin >> Pi;
            for (int j = 1; j <= Pi; j++)
            {
                cin >> identifiers;
                leftPan[i].insert(identifiers);
            }
            
            for (int j = 1; j <= Pi; j++)
            {
                cin >> identifiers;
                rightPan[i].insert(identifiers);                
            }
            
            cin >> result[i];
        }
        
        int possibility = 0, falseCoin = -1;
        for (int i = 1; i <= N; i++)
        {
            for (int w = 0; w <= 2; w += 2)
            {
                bool conformed = true;
                for (int j = 1; j <= K; j++)
                {
                    int leftPanWeight = leftPan[j].find(i) != leftPan[j].end() ? w : 1;
                    int rightPanWeight = rightPan[j].find(i) != rightPan[j].end() ? w : 1;
                    
                    if (leftPanWeight < rightPanWeight && result[j] == '<') continue;
                    if (leftPanWeight > rightPanWeight && result[j] == '>') continue;
                    if (leftPanWeight == rightPanWeight && result[j] == '=') continue;
                    
                    conformed = false;
                    break;
                }
                
                if (conformed)
                {
                    possibility += 1, falseCoin = i;
                    break;
                }
            }
        }
        
        if (possibility == 1) cout << falseCoin << '\n';
        else cout << "0\n";
    }
    
    return 0;
}
