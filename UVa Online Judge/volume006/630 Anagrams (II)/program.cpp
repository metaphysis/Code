// Anagrams (II)
// UVa ID: 630
// Verdict: Accepted
// Submission Date: 2016-08-16
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

    string words[1100], sorted[1100];
    int word_count = 0, cases = 0;
    
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';
            
        cin >> word_count;
        for (int i = 0; i < word_count; i++)
        {
            cin >> words[i];
            sorted[i] = words[i];
            sort(sorted[i].begin(), sorted[i].end());
        }
        
        string word, backup;
        while (cin >> word, word != "END")
        {
            backup = word;
            sort(word.begin(), word.end());
            cout << "Anagrams for: " << backup << '\n';
            int count = 1;
            for (int i = 0; i < word_count; i++)
                if (word == sorted[i])
                {
                    cout << setw(3) << right << count;
                    cout << ") " << words[i] << '\n';
                    count++;
                }
            if (count == 1)
                cout << "No anagrams for: " << backup << '\n';
        }
            
    }
    
	return 0;
}
