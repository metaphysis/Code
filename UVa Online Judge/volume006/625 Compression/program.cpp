// Compression
// UVa ID: 625
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    map<string, int> keywords = {
        {"var", 0}, {"end", 1}, {"for", 2}, {"then", 3}, {"else", 4},
        {"case", 5}, {"goto", 6}, {"const", 7}, {"label", 8}, {"while", 9},
        {"begin", 10}, {"until", 11}, {"repeat", 12}, {"downto", 13},
        {"function", 14}, {"procedure", 15}
    };

    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';

        getline(cin, line);
        
        map<string, int> vars;
        int count = 16;
        while (getline(cin, line), line != "end.")
        {
            int i = 0;
            while (i < line.length())
            {
                if (isalpha(line[i]) || isdigit(line[i]))
                {
                    string block;
                    while (i < line.length() && (isalpha(line[i]) || isdigit(line[i])))
                    {
                        block += line[i];
                        i++;
                    }
                    
                    if (keywords.find(block) != keywords.end())
                        cout << '&' << keywords[block];
                    else
                    {
                        bool alphanumeric = true;
                        for (int j = 0; j < block.length(); j++)
                            if (!isalpha(block[j]) && !isdigit(block[j]))
                            {
                                alphanumeric = false;
                                break;
                            };
                        if (alphanumeric)
                        {
                            if (block.length() < 3)
                                cout << block;
                            else
                            {
                                if (vars.find(block) != vars.end())
                                {
                                    cout << '&' << vars[block];
                                }
                                else
                                {
                                    vars[block] = count++;
                                    cout << block;
                                }
                            }
                        }
                        else
                            cout << block;
                    }
                }
                else
                    cout << line[i++];
            }
            cout << '\n';
        }
        cout << "&1.\n";
    }
    
	return 0;
}
