// Luggage
// UVa ID: 10664
// Verdict: Accepted
// Submission Date: 2017-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 320;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);
    
    int F[MAXN], C[MAXN], N, S;

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        istringstream iss(line);
        
        N = S = 0;
        
        while (iss >> C[N])
        {
            S += C[N];
            N++;
        }
        
        if ((S % 2) == 1) 
        {
            cout << "NO\n";
            continue;
        }
        
        memset(F, 0, sizeof(F));
        F[0] = 1;
        
        for (int i = 0; i < N; i++)
            for (int j = S; j >= C[i]; j--)
                F[j] |= F[j - C[i]];
                
        if (F[S / 2]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
