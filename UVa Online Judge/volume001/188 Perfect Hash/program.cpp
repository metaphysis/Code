// Perfect Hash
// UVa IDs: 188
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > words;

bool test(long long C)
{
    vector < int > used;
    for (int i = 0; i < words.size(); i++)
        used.push_back(true);
      
    for (int i = 0; i < words.size(); i++)
    {
        int remainder = C / words[i] % words.size();
        if (used[remainder] == false)
            return false;
        else
            used[remainder] = true;
    }
            
        
    return true;
}

long long find()
{
    long long C = 1;
    int n = words.size();
    
    do
    {
        long long oldC = C;
        for (int i = 0; i < words.size(); i++)
        {
            
            C = max(
        }
        
    } while (test() == false);
    
    return C;
}

int main(int argc, char *argv[])
{
    string line, block;
    while (getline(cin, line))
    {
        istringstream iss(line);
        while (iss >> block)
        {
            int number = 0;
            for (int i = 0; i < block.length(); i++)
                number = number * 32 + block[i] - 'a' + 1;
            words.push_back(number);
            
            sort(words.begin(), words.end());
            
            cout << line << "\n";
            cout << find() << "\n";
        }
    }
    
	return 0;
}
