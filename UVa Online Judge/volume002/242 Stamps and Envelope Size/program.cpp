// Stamps and Envelope Size
// UVa IDs: 242
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

int value[11][1001], denomination[11], appeared[1010];
int best[11], bestD;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int S;
    while (cin >> S, S)
    {
        int N;
        cin >> N;
        
        int maxValue = 0, bestD = 11;
        for (int i = 1; i <= N; i++)
        {
            int D;
            cin >> D;
            
            for (int j = 0; j < D; j++)
                cin >> denomination[j];
            
            memset(value, 0, sizeof(value));
            memset(appeared, 0, sizeof(appeared));
            
            value[0][0] = 1;

            for (int j = 1; j <= S; j++)
                for (int k = 0; k < 1001; k++)
                    if (value[j - 1][k])
                        for (int m = 0; m < D; m++)
                        {
                            value[j][k + denomination[m]] = 1;
                            appeared[k + denomination[m]] = 1;
                        }
            int index;
            for (index = 1; index < 1010; index++)
                if (appeared[index] == 0)
                    break;
            index--;
            
            if (index > maxValue)
            {
                bestD = D;
                for (int i = 0; i < D; i++)
                    best[i] = denomination[i];
            }
            else if (index == maxValue && D < bestD)
            {
                bestD = D;
                for (int j = 0; j < D; j++)
                    best[j] = denomination[j];
            }
            else if (index == maxValue && D == bestD)
            {
                for (int j = D - 1; j >= 0; j--)
                {
                    if (denomination[j] > best[j])
                        break;
                    if (denomination[j] == best[j])
                        continue;
                    for (int k = 0; k < D; k++)
                        best[k] = denomination[k];
                    break;
                }
                
            }
            
            maxValue = max(index, maxValue);
        }
        
        cout << "max coverage =" << setw(4) << right << maxValue << " :";
        for (int i = 0; i < bestD; i++)
            cout << setw(3) << right << best[i];
        cout << endl;
    }
    
	return 0;
}
