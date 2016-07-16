// Romulan Spelling
// UVa ID: 373
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

    string text;
    while (getline(cin, text))
    {
        if (text.find('#') != text.npos) assert(false);
        
        vector<string> memory;
        size_t i = 0;
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
            for (int j = text.length() - 1; j >= 1; j--)
                if (toupper(text[j]) == 'G' && toupper(text[j - 1]) == 'P')
                    swap(text[j], text[j - 1]), updated = true;
            if (!updated) break;
        }

        // gpuk => pguk
        int length = text.length();
        while (true)
        {
            bool updated = false;
            for (int j = 0; j <= length - 4; j++)
            {
                if (toupper(text[j]) == 'G' && toupper(text[j + 1]) == 'P' &&
                    toupper(text[j + 2]) == 'U' && toupper(text[j + 3]) == 'K')
                        swap(text[j], text[j + 1]), updated = true;
            }
            if (!updated) break;
        }
        
        // egp => epg 
        while (true)
        {
            bool updated = false;
            for (int j = 0; j <= length - 3; j++)
                if (toupper(text[j]) == 'E' && toupper(text[j + 1]) == 'G' &&
                    toupper(text[j + 2]) == 'P')
                    swap(text[j + 1], text[j + 2]), updated = true;
            if (!updated) break;
        }

        int indexer = 0;
        for (auto element : text)
            if (element == '#') cout << memory[indexer++];
            else cout << element;
            
        cout << endl;
    }

	return 0;
}
