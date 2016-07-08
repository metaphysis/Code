// Romulan Spelling
// UVa IDs: 373
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line, text;
    while (getline(cin, line)) text += line + '\n';

    assert(text.length() <= 5000000);
    
    vector<string> memory;
    int i = 0;
    while (i < text.length())
    {
        if (toupper(text[i]) == 'E')
        {
            if (i <= text.length() - 5 && toupper(text[i + 1]) == 'P')
            {
                if (toupper(text[i + 2]) == 'G' && toupper(text[i + 3]) == 'U' && toupper(text[i + 4]) == 'K')
                {
                    memory.push_back(text.substr(i, 5));
                    text[i] = '#';
                    text.erase(text.begin() + i + 1, text.begin() + i + 5);
                    continue;
                }
            }
            
            if (i <= text.length() - 3 && toupper(text[i + 1]) == 'P' && toupper(text[i + 2]) == 'G')
            {
                memory.push_back(text.substr(i, 3));
                text[i] = '#';
                text.erase(text.begin() + i + 1, text.begin() + i + 3);
            }
        }
        else if (toupper(text[i]) == 'P')
        {
            if (i <= text.length() - 4 && toupper(text[i + 1]) == 'G')
                if (toupper(text[i + 2]) == 'U' && toupper(text[i + 3]) == 'K')
                {
                    memory.push_back(text.substr(i, 4));
                    text[i] = '#';
                    text.erase(text.begin() + i + 1, text.begin() + i + 4);
                }
        }
        
        i++;
    }

    // pg => gp
    while (true)
    {
        bool updated = false;
        for (int i = text.length() - 1; i >= 0; i--)
            if (toupper(text[i]) == 'G' && i >= 1 && toupper(text[i - 1]) == 'P')
                swap(text[i], text[i - 1]), updated = true;
        if (!updated) break;
    }
    
    // gpuk => pguk
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < text.length(); i++)          
            if (toupper(text[i]) == 'G')
            {
                if (i <= text.length() - 4 && toupper(text[i + 1]) == 'P')
                    if (toupper(text[i + 2]) == 'U' && toupper(text[i + 3]) == 'K')
                        swap(text[i], text[i + 1]), updated = true;
            }
        if (!updated) break;
    }
    
    // egp => epg
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < text.length(); i++)
            if (toupper(text[i]) == 'E')
            {
                if (i <= text.length() - 3 && toupper(text[i + 1]) == 'G')
                    if (toupper(text[i + 2]) == 'P')
                        swap(text[i + 1], text[i + 2]), updated = true;
            }            
        if (!updated) break;
    }
    
    int indexer = 0;
    for (auto element : text)
        if (element == '#') cout << memory[indexer++];
        else cout << element;
    
	return 0;
}
