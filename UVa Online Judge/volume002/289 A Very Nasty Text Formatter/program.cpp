// A Very Nasty Text Formatter
// UVa IDs: 289
// Verdict: Accepted
// Submission Date: 2016-06-07
// UVa Run Time: 0.750s
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

vector <string> words;
int n;

void process()
{
    vector <string> buffer;
    
    int length = 0;
    while (words.size())
    {
        if (length + buffer.size() + words.front().length() <= n)
        {
            length += words.front().length();
            buffer.push_back(words.front());
            words.erase(words.begin());
        }
        else
            break;
    }
    
    if (buffer.size() == 0)
    {
        int cut = n - 1;
        cout << words.front().substr(0, cut) << "-" << endl;
        words.front() = words.front().substr(cut);
    }
    else if (buffer.size() == 1)
    {
        if (words.size() && (buffer.front().length() + 3 <= n))
        {
            string next_word = words.front();
            int cut = n - buffer.front().length() - 2;
            cout << buffer.front() << " " << next_word.substr(0, cut);
            cout << "-" << endl;
            words.front() = next_word.substr(cut);
        }
        else
            cout << buffer.front() << endl;
    }
    else
    {
        if (words.size())
        {
            int space = n - length;
            
            while (space > 0)
            {
                for (int i = 0; i < buffer.size() - 1 && space > 0; i++)
                {
                    buffer[i] += ' ';
                    space--;
                }
            }
        }
        else
        {
            for (int i = 0; i < buffer.size() - 1; i++)
                buffer[i] += ' ';
        }
        
        for (int i = 0; i < buffer.size(); i++)
            cout << buffer[i];
        cout << endl;
    }
    
    if (words.size())
        process();
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        words.clear();
        string word;
        istringstream iss(line);
        while (iss >> word)
            words.push_back(word);
            
        n = stoi(words.front());
        words.erase(words.begin());
        
        process();
    }
    
	return 0;
}
