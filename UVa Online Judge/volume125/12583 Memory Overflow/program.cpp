// Memory Overflow
// UVa ID: 12583
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

    int cases, memory[26], n, k;
    char people;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        
        for (int i = 0; i < 26; i++)
            memory[i] = -1000;

        int days = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> people;
            if (i - memory[people - 'A'] <= k) days++;
            memory[people - 'A'] = i;
        }
        
        cout << "Case " << c << ": " << days << '\n';
    }
    
    return 0;
}
