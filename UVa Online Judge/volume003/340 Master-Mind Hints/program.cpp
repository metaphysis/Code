// Master-Mind Hints
// UVa IDs: 340
// Verdict: Accepted
// Submission Date: 2016-06-27
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
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int secret[1100], guess[1100], n, cases = 0;
    
    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
            cin >> secret[i];
        
        cout << "Game " << ++cases << ":" << endl;
            
        while (true)
        {
            int strong = 0;
            
            map<int, int> S, G;
            for (int i = 1; i <= n; i++)
            {
                cin >> guess[i];
                if (secret[i] == guess[i])
                    strong++;
                else
                {
                    S[secret[i]]++;
                    G[guess[i]]++;
                }
            }
            
            if (guess[1] == 0)
                break;
            
            int weak = 0;    
            for (auto pair : S)
                if (G.find(pair.first) != G.end())
                    weak += min(pair.second, G[pair.first]);
            
            cout << "    (" << strong << "," << weak << ")" << endl;
        }
    }
    
	return 0;
}
