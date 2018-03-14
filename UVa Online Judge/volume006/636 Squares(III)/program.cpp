// Squares(III)
// UVa ID: 636
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "0")
    {
        int min_base = 2;
        for (int i = 0; i < line.length(); i++)
        {
            int digit = line[i] - '0';
            if (digit >= min_base)
                min_base = digit + 1;
        }

        for (int b = min_base; b < 100; b++)
        {
            long long int n = 0;
            for (int i = 0; i < line.length(); i++)
                n = n * b + line[i] - '0';
            long long int root = sqrt(n);
            if (root * root == n || (root - 1) * (root - 1) == n || (root + 1) * (root + 1) == n)
            {
                cout << b << '\n';
                break;
            }
        }
    }
    
	return 0;
}
