// Anagrams by Stack
// UVa ID: 732
// Verdict: Accepted
// Submission Date: 2017-02-17
// UVa Run Time: 0.060s
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
#include <vector>

using namespace std;

string from, to;

void backtrack(string letters, int source, int dest, string sequences)
{
    if (dest >= to.length())
    {
        for (int i = 0; i < sequences.length(); i++)
        {
            if (i > 0) cout << ' ';
            cout << sequences[i];
        }
        cout << '\n';
        return;
    }
    
    if (source < from.length())
    {
        backtrack(letters + from[source], source + 1, dest, sequences + 'i');
    }

    if (letters.length() > 0 && letters.back() == to[dest])
    {
        letters.erase(letters.end() - 1);
        backtrack(letters, source, dest + 1, sequences + 'o');
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> from >> to)
    {
        if (from.length() != to.length())
        {
            cout << "[\n]\n";
            continue;
        }
        
        cout << "[\n";
        
        string letters, sequences;
        backtrack(letters, 0, 0, sequences);

        cout << "]\n";
    }
    
    return 0;
}
