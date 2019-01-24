// Document Validator
// UVa ID: 831
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(256, '\n');
    for (int cs = 1; cs <= cases; cs++)
    {
        string text, line;
        while (getline(cin, line), line.length() > 0)
            text += line;

        bool error = false;
        stack<int> opening;
        stack<string> blocks;
        int i = 0;
        while (i < text.length())
        {
            if (text[i] == '[' || text[i] == ']' || text[i] == '{' || text[i] == '}')
            {
                if (text[i] == '[' || text[i] == '{')
                {
                    if (text[i] == '[') opening.push(0);
                    if (text[i] == '{') opening.push(1);
                    
                    string block;
                    while (i < text.length() && !isblank(text[i]))
                    {
                        block += text[i];
                        i++;
                    }
                    blocks.push_back(block);
                }
                else
                {
                }
                while (i < text.length())
                {
                    if (text[i] == '[' || text[i] == ']' || text[i] == '{' || text[i] != '}') break;
                    i++;
                }
            else if (!isblank(text[i]))
            {
            }
            else
            {
            }
        }
    }

    return 0;
}
