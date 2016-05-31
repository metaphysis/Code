// Compress
// UVa IDs: 283
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

int findMinimumLength(vector <int> count, vector <int> length)
{
    reverse(count.begin(), count.end());
    for (int i = 0; i < count.size(); i++)
        cout << setw(3) << right << count[i];
    cout << endl;
    
    for (int i = 0; i < length.size(); i++)
        cout << setw(3) << right << length[i];
    cout << endl;
    
    cout << "----" << endl;
    
    int sum = 0;
    for (int i = 0; i < count.size(); i++)
        sum += count[i] * length[i];
        
    cout << sum << endl;
    cout << "----" << endl;
    return sum;
}

int main(int argc, char *argv[])
{
    int cases;
    
    string line;
    getline(cin, line);
    cases = stoi(line);
    
    while (cases--)
    {
        int n;
        getline(cin, line);
        n = stoi(line);
        
        string text;
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            text += line;
        }
        
        map<char, int> frequency;
        for (int i = 0; i < text.length(); i++)
            frequency[text[i]]++;
        
        vector <int> count, length;
        for (auto it = frequency.begin(); it != frequency.end(); it++)
            count.push_back((*it).second);
        sort(count.begin(), count.end());
        
        int maxLength = 1, base = 2;
        while (base < count.size())
            maxLength++, base *= 2;
        
        int minLength = numeric_limits<int>::max();
        for (int i = 1, baseCount = 2; i <= maxLength; i++, baseCount *= 2)
        {
            length.clear();
            
            int codeCount = baseCount, codeLength = i;
            
            while (true)
            {
                if (length.size() + codeCount >= count.size())
                {
                    for (int j = 1; j <= codeCount && length.size() < count.size(); j++)
                        length.push_back(codeLength);
                }
                else
                {
                    for (int j = 1; j < codeCount; j++)
                        length.push_back(codeLength);
                }
                
                if (length.size() >= count.size())
                    break;
                    
                codeLength += i;
            }
            
            minLength = min(minLength, findMinimumLength(count, length));
        }
        
        cout << minLength << endl;
    }
    
	return 0;
}
