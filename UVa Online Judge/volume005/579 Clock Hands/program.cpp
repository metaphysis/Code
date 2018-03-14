// Clock Hands
// UVa ID: 579
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line, H, M;
    while (getline(cin, line), line != "0:00")
    {
        istringstream iss(line);
        getline(iss, H, ':');
        getline(iss, M, ':');
        
        //cout << H << ':' << M << '\n';
        
        int hours = stoi(H), minutes = stoi(M);

        int numerator = abs(60 * hours - 11 * minutes);
        if (numerator > 360)
            numerator = 720 - numerator;

        cout << fixed << setprecision(3) << ((double)(numerator) / 2.0) << '\n';
    }
    
	return 0;
}
