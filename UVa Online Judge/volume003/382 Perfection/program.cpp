// Perfection
// UVa ID: 382
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    cout << "PERFECTION OUTPUT" << endl;
    
    int n;
    while (cin >> n, n)
    {
        int sum = 0;
        for (int i = 1; i < n; i++)
            if (n % i == 0)
                sum += i;
                
        cout << setw(5) << right << n;
        cout << "  ";
        if (sum == n) cout << "PERFECT" << endl;
        else if (sum < n) cout << "DEFICIENT" << endl;
        else cout << "ABUNDANT" << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
	return 0;
}
