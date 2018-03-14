// Uniform Generator
// UVa ID: 408
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int STEP, MOD;
    
    while (cin >> STEP >> MOD)
    {
        cout << setw(10) << right << STEP;
        cout << setw(10) << right << MOD;
        cout << string(4, ' ');
        
        int temp, a = STEP, b = MOD;
        while (a % b) temp = a, a = b, b = temp % b;
        
        if (b == 1) cout << "Good Choice\n\n";
        else cout << "Bad Choice\n\n";
    }
    
	return 0;
}
