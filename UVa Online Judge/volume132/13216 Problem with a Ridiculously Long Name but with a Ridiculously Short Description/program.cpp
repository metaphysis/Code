// Problem with a Ridiculously Long Name but with a Ridiculously Short Description
// UVa ID: 13216
// Verdict: Accepted
// Submission Date: 2017-11-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string n;
    int cases, tail[5] = {76, 16, 56, 96, 36};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        if (n == "0") { cout << "1\n"; continue; }
        if (n == "1") { cout << "66\n"; continue; }
        
        int r = 0;
        for (int i = 0; i < n.length(); i++)
        {
            r = r * 10 + n[i] - '0';
            r %= 5;
        }
        
        cout << tail[r] << '\n';
    }

    return 0;
}
