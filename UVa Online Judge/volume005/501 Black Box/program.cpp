// Black Box
// UVa ID: 501
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 1.110s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    long long int K, M, N, number[30001];
    cin >> K;
    
    for (int cases = 1; cases <= K; cases++)
    {
        if (cases > 1) cout << '\n';
        
        cin >> M >> N;
        
        for (int i = 0; i < M; i++)
            cin >> number[i];
        
        int u;    
        for (int i = 0; i < N; i++)
        {
            cin >> u;
            nth_element(number, number + i, number + u);
            cout << number[i] << '\n';
        }
    }
    
	return 0;
}
