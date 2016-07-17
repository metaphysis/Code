// Anagrams
// UVa ID: 454
// Verdict: Accepted
// Submission Date: 2016-07-17
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
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        vector<string> words;
        map<string, string> sorted;

        while (getline(cin, line), line.length() > 0)
        {
            words.push_back(line);
            
            for (int i = line.length() - 1; i >= 0; i--)
                if (isblank(line[i]))
                    line.erase(line.begin() + i);
                    
            sort(line.begin(), line.end());
            sorted[words.back()] = line;
        }

        sort(words.begin(), words.end());
        
        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
                if (sorted[words[i]] == sorted[words[j]])
                    cout << words[i] << " = " << words[j] << '\n';
    }
    
	return 0;
}
