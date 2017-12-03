// The Mad Numerologist
// UVa ID: 10785
// Verdict: Accepted
// Submission Date: 2017-12-03
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

bool isVowels(char c)
{
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, counter[26];
    char vowels[5] = {'A', 'U', 'E', 'O', 'I'};
    char consonants[21] = {'J', 'S', 'B', 'K', 'T', 'C', 'L', 'D', 'M', 'V', 'N', 'W', 'F', 'X', 'G', 'P', 'Y', 'H', 'Q', 'Z', 'R'};
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << "Case " << c << ": ";
        
        memset(counter, 0, sizeof(counter));

        string name;
        int vi = 0, ci = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i & 1)
            {
                if (counter[vi] >= 21) vi++;
                name += vowels[vi];
                counter[vi]++;
            }
            else
            {
                if (counter[ci + 5] >= 5) ci++;
                name += consonants[ci];
                counter[ci + 5]++;
            }
        }
        sort(name.begin(), name.end());
        vi = 0, ci = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i & 1) 
            {
                while (!isVowels(name[vi])) vi++;
                cout << name[vi++];
            }
            else
            {
                while (isVowels(name[ci])) ci++;
                cout << name[ci++];
            }
        }
        cout << '\n';
    }

    return 0;
}
