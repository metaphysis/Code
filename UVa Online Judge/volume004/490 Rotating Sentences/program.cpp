// Rotating Sentences
// UVa ID: 490
// Verdict: Accepted
// Submission Date: 2016-07-13
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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int max_length = 0;
    vector<string> sentences;
    string line;
    while (getline(cin, line))
    {
        for (int i = line.length() - 1; i >= 0; i--)
            if (line[i] == '\t')
                line.erase(line.begin() + i);
        max_length = max(max_length, (int)line.length());        
        sentences.push_back(line);
    }
    
    for (int i = 0; i < max_length; i++)
    {
        for (int j = sentences.size() - 1; j >= 0; j--)
            if (i < sentences[j].length())
                cout << sentences[j][i];
            else
                cout << ' ';
        cout << endl;
    }
    
	return 0;
}
