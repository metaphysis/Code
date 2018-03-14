// Password Search
// UVa ID: 902
// Verdict: Accepted
// Submission Date: 2017-01-09
// UVa Run Time: 0.490s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    string text;
    
    while (cin >> n >> text)
    {
        map<string, int> counter;
        for (int i = 0; i <= text.length() - n; i++)
            counter[text.substr(i, n)]++;

        int max = 0;
        string password;
        for (auto pair : counter)
            if (pair.second > max)
            {
                max = pair.second;
                password = pair.first;
            }
            
        cout << password << '\n';
    }
    
    return 0;
}
