// Mother Bear
// UVa ID: 10945
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        if (line == "DONE") break;
        string tripped;
        for (int i = 0; i < line.length(); i++)
            if (isalpha(line[i]))
                tripped += tolower(line[i]);
        
        bool flag = true;
        for (int i = 0, j = tripped.length() - 1; i <= j; i++, j--)
        {
            if (tripped[i] != tripped[j])
            {
                flag = false;
                break;
            }
        }
        
        if (flag) cout << "You won't be eaten!\n";
        else cout << "Uh oh..\n";
    }

    return 0;
}
