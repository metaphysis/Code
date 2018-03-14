// Forests
// UVa ID: 10227
// Verdict: Accepted
// Submission Date: 2018-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        int P, T, p, t;

        cin >> P >> T;
        cin.ignore(1024, '\n');
        
        bitset<100> heard[P];

        string line;
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            iss >> p >> t;
            heard[p - 1].set(t - 1);
        }
        
        set<string> opinions;
        for (int i = 0; i < P; i++)
            opinions.insert(heard[i].to_string());

        if (c > 1) cout << '\n';
        cout << opinions.size() << '\n';
    }

    return 0;
}
