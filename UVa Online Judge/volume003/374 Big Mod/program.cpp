// Big Mod
// UVa ID: 374
// Verdict: Accetped
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

long long int mod(long long int B, long long int P, long long int M)
{
    if (P == 1)
        return B % M;
    
    if (P == 2)
        return (B * B) % M;
    
    long long int m = mod(B, P / 2, M);
    m *= m;
    if (P % 2 == 1) m *= B;
    
    return m % M;
}

int main(int argc, char *argv[])
{
    long long int B, P, M;
    
    while (cin >> B >> P >> M)
    {
        if (P == 0)
        {
            cout << 1 % M << endl;
            continue;
        }
        
        if (B % M == 0)
        {
            cout << "0" << endl;
            continue;
        }
        
        cout << mod(B % M, P, M) << endl;
    }
    
	return 0;
}
