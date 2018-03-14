// Movie Police
// UVa ID: 12515
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.180s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, Q, L;
    int movie[1010][110], clip[110], length[1010];
    string bits;

    while (cin >> M >> Q)
    {       
        for (int i = 0; i < M; i++)
        {
            cin >> bits;
            for (int j = 0; j < bits.size(); j++)
                movie[i][j] = bits[j] - '0';
            length[i] = bits.size();
        }
        
        for (int i = 0; i < Q; i++)
        {
            cin >> bits;
            
            int L = bits.length();
            for (int j = 0; j < bits.size(); j++)
                clip[j] = bits[j] - '0';
            
            int selected = 0, matchedMost = 0;
            for (int j = 0; j < M; j++)
            {
                if (L > length[j]) continue;
                
                int tested = length[j] - L;
                for (int k = 0; k <= tested; k++)
                {
                    int similarity = 0;
                    for (int l = 0; l < L; l++)
                        if (clip[l] == movie[j][k + l])
                            similarity++;
                    if (similarity > matchedMost)
                    {
                        selected = j + 1;
                        matchedMost = similarity;
                    }     
                }
                if (matchedMost == L) break;
            }
            
            cout << selected << '\n';
        }
    }
    
    return 0;
}
