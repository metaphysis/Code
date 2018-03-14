// Fun Coloring
// UVa ID: 12348
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, number[120][3], cnt[120];
    char buffer[1024];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        
        cin.ignore(1024, '\n');
        
        memset(cnt, 0, sizeof(cnt));

        for (int i = 0; i < m; i++)
        {
            cin.getline(buffer, 1024);
            
            int t = 0;
            for (int j = 0; buffer[j]; j++)
            {
                if (buffer[j] == ' ' || buffer[j] == '\t')
                {
                    if (t > 0) number[i][cnt[i]++] = t;
                    t = 0;
                    continue;
                }
                
                t = t * 10 + buffer[j] - '0';
            }
            
            if (t > 0) number[i][cnt[i]++] = t;
        }

        bool flag;
        for (int i = 0; i < (1 << n); i++)
        {
            flag = true;
            for (int j = 0; j < m; j++)
            {
                int a = 0, b = 0;

                for (int k = 0; k < cnt[j]; k++)
                    if (i & (1 << (number[j][k] - 1)))
                        a++;
                    else
                        b++;
                if ((a == 0 && b == 1) || (a == 1 && b == 0) ||
                    (a == 1 && b == 1) ||
                    (a == 1 && b == 2) || (a == 2 && b == 1))
                    continue;
                    
                flag = false;
                break;
            }

            if (flag) break;
        }

        cout << (flag ? 'Y' : 'N');
    }
    
    return 0;
}
