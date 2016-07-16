// Word Index
// UVa ID: 417
// Verdict: Accepted
// Submission Date: 2016-07-15
// UVa Run Time: 0.020s
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

map<string, int> indexer;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string letters = "abcdefghijklmnopqrstuvwxyz";
    int counter = 1;
    queue<string> generator;
    
    for (int i = 0; i < letters.length(); i++)
    {
        generator.push(string(1, letters[i]));
        indexer[string(1, letters[i])] = counter++;
    }
    
    while (!generator.empty())
    {
        string current = generator.front();
        generator.pop();
        
        if (current.length() == 5) continue;
        
        for (int i = 0; i < letters.length(); i++)
        {
            if (letters[i] > current.back())
            {
                generator.push(current + letters[i]);
                indexer[current + letters[i]] = counter++;
            }
        }
    }
    
    string line;
    while (cin >> line)
    {
        bool valid = true;
        for (int i = 0; i < line.length() - 1; i++)
            if (line[i] >= line[i + 1])
            {
                valid = false;
                break;
            }
            
        if (!valid)
        {
            cout << "0" << endl;
            continue;
        }
        
        cout << indexer[line] << endl;
    }
    
	return 0;
}
