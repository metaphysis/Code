// Perfect Hash
// UVa IDs: 188
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > words;

bool test(long long C)
{
    vector < int > used;
    for (int i = 0; i < words.size(); i++)
        used.push_back(false);
      
    for (int i = 0; i < words.size(); i++)
    {
        int remainder = C / words[i] % words.size();
        if (used[remainder] == true)
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
        for (int i = 0; i < words.size() - 1; i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                if ((oldC / words[i] % n) == (oldC / words[j] % n))
                    C = max(C, min((oldC / words[i] + 1) * words[i],
                        (oldC / words[j] + 1) * words[j])); 
            }
    } while (test(C) == false);
    
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
        }
        
        sort(words.begin(), words.end());
        
        cout << line << "\n";
        cout << find() << "\n\n";
        
        words.clear();
    }
    
	return 0;
}
