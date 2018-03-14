// Just the Facts
// UVa ID: 568
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long int MOD = 100000000000;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long int last_number[10001] = { 1 };
    for (int i = 1; i <= 10000; i++)
    {
        long long int temp = i;
        while (temp % 10 == 0) temp /= 10;
        temp *= last_number[i - 1];
        while (temp % 10 == 0) temp /= 10;
        if (temp > MOD) temp %= MOD;
        last_number[i] = temp;
    }
    
    int n;
    while (cin >> n)
        cout << setw(5) << right << n << " -> " << (last_number[n] % 10) << '\n';
    
	return 0;
}
