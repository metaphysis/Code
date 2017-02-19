// Anagrams by Stack
// UVa ID: 732
// Verdict: Accepted
// Submission Date: 2017-02-17
// UVa Run Time: 0.010s
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
string letters(110, '0'), sequences(110, '0');
int letters_idx, sequences_idx;

void backtrack(int sequences_idx, int source, int dest)
{
    if (dest >= to.length())
    {
        for (int i = 0; i < sequences_idx; i++)
        {
            if (i > 0) cout << ' ';
            cout << sequences[i];
        }
        cout << '\n';
        return;
    }

    if (source < from.length())
    {
        letters[letters_idx++] = from[source];
        sequences[sequences_idx] = 'i';

        backtrack(sequences_idx + 1, source + 1, dest);
        
        letters_idx--;
    }

    if (letters_idx > 0 && letters[letters_idx - 1] == to[dest])
    {
        sequences[sequences_idx] = 'o';
        letters_idx--;

        backtrack(sequences_idx + 1, source, dest + 1);

        letters[letters_idx++] = to[dest];
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

        letters_idx = 0;
        backtrack(0, 0, 0);

        cout << "]\n";
    }
    
    return 0;
}
