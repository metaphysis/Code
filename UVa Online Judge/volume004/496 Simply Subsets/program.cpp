// Simply Subsets
// UVa ID: 496
// Verdict: Accepted
// Submission Date: 2016-07-16
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

    string line;
    while (getline(cin, line))
    {
        set<int> A, B;
        
        int number;
        istringstream iss(line);
        while (iss >> number)
            A.insert(number);
        
        getline(cin, line);
        iss.clear(); iss.str(line);
        while (iss >> number)
            B.insert(number);
        
        set<int> shared;
        for (auto a : A)
        {
            if (B.find(a) != B.end())
                shared.insert(a);
        }
        
        if (shared.size() == A.size() && shared.size() == B.size())
        {
            cout << "A equals B\n";
        }
        else if (shared.size() == 0)
        {
            cout << "A and B are disjoint\n";
        }
        else if (shared.size() == A.size())
        {
            cout << "A is a proper subset of B\n";
        }
        else if (shared.size() == B.size())
        {
            cout << "B is a proper subset of A\n";
        }
        else
            cout << "I'm confused!\n";
    }
    
	return 0;
}
