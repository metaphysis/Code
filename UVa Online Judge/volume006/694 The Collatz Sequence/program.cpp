// The Collatz Sequence
// UVa ID: 694
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.020s
	
#include <bits/stdc++.h>

using namespace std;

	
int main(int ac, char *av[])
{
    ios::sync_with_stdio(false);
    
	int cases = 0;
    long long A, L;
    
	while (cin >> A >> L)
	{
		if (A <= 0 || L <= 0) break;
		
		int terms = 1; long long T = A;
		while (T > 1)
		{
		    if (T % 2 == 0) T /= 2;
		    else T = T * 3 + 1;
		    if (T > L) break;
		    terms++;
		}
		
		cout << "Case " << ++cases << ": A = " << A;
		cout << ", limit = " << L << ", number of terms = " << terms << endl;
		
	}
	
	return 0;
}
