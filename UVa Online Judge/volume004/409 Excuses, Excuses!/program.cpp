// Excuses, Excuses!
// UVa ID: 409
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

    string word, line;
    int K, E, cases = 0;
    while (cin >> K >> E)
    {
        cout << "Excuse Set #" << ++cases << '\n';
        
        set<string> keywords;
        vector<string> execuses;
        vector<int> frequencies;
        for (int i = 1; i <= K; i++)
        {
            cin >> word;
            keywords.insert(word);
        }
        
        cin.ignore(1024, '\n');
        for (int i = 1; i <= E; i++)
        {
            getline(cin, line);
            execuses.push_back(line);
            for (int i = 0; i < line.length(); i++)
                line[i] = tolower(line[i]);
            
            int index = 0, frequency = 0;
            while (index < line.length())
            {
                if (isalpha(line[index]))
                {
                    string block;
                    while (index < line.length() && isalpha(line[index]))
                    {
                        block += line[index];
                        index++;
                    }
                    if (keywords.find(block) != keywords.end())
                        frequency++;
                }
                else
                    index++;
            }
            
            frequencies.push_back(frequency);
        }
        
        int max_frequency = *max_element(frequencies.begin(), frequencies.end());
        for (int i = 0; i < frequencies.size(); i++)
            if (frequencies[i] == max_frequency)
                cout << execuses[i] << '\n';
                
        cout << '\n';
    }
    
	return 0;
}
