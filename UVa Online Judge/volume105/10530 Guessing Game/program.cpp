// Guessing Game
// UVa ID: 10530
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string word1, word2;
    
    while (cin >> n, n > 0)
    {
        int up = 10, low = 1;
        int cheated = 0;
        do
        {
            cin >> word1 >> word2;
            if (word2 == "on")
            {
                if (n < low || n > up) cheated = 1;
                break;
            }
            if (n >= up && word2 == "low") cheated = 1;
            if (n <= low && word2 == "high") cheated = 1;
            if (cheated) continue;
            if (word2 == "high") up = min(n - 1, up);
            else if (word2 == "low") low = max(n + 1, low);
            if (up < low) cheated = 1;
        } while (cin >> n);
        
        cout << (cheated ? "Stan is dishonest\n" : "Stan may be honest\n");
    }

    return 0;
}
