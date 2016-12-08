// Substitution Cypher
// UVa ID: 865
// Verdict: Accepted
// Submission Date: 2016-12-08
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

    int cases = 0, mapped[256];
    string line, plaintext, substitution;
    
    getline(cin, line);
    cases = stoi(line);
    getline(cin, line);
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        getline(cin, plaintext);
        getline(cin, substitution);
        
        cout << substitution << '\n';
        cout << plaintext << '\n';
        
        memset(mapped, 0, sizeof(mapped));
        for (int i = 0; i < plaintext.length(); i++)
            mapped[plaintext[i]] = substitution[i];

        while (getline(cin, line), line.length() > 0)
        {
            for (int i = 0; i < line.length(); i++)
                if (mapped[line[i]]) cout << (char)mapped[line[i]];
                else cout << line[i];
            cout << '\n';
        }
    }
    
	return 0;
}
