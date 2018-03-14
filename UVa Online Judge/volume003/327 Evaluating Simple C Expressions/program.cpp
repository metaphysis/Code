// Evaluating Simple C Expressions
// UVa ID: 327
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.210s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string variable = "abcdefghijklmnopqrstuvwxyz";
    
    map<char, int> expression;
    for (int i = 0; i < variable.length(); i++)
        expression[variable[i]] = i + 1;
    
    map<string, char> finder;
    finder.insert(make_pair("++", '&')), finder.insert(make_pair("--", '|'));
            
    string line;
    while (getline(cin, line))
    {
        string changed;
        for (int i = 0; i < line.length(); i++)
        {
            if (isblank(line[i]))
                continue;   
            changed += line[i];
        }
        
        for (auto pair : finder)
        {
            int start = 0, next = changed.find(pair.first, start);
            while (next != changed.npos)
            {
                changed[next] = pair.second, changed[next + 1] = ' ';
                start = next + 2;
                next = changed.find(pair.first, start);
            }
        }
        
        for (int i = changed.length() - 1; i >= 0; i--)
            if (isblank(changed[i]))
                changed.erase(changed.begin() + i);
        
        map<char, int> before, after;
        for (int i = 0; i < changed.length(); i++)
        {
            if (changed[i] == '&' || changed[i] == '|')
            {
                int offset = changed[i] == '&' ? 1 : -1;
                if (i + 1 < changed.length() && isalpha(changed[i + 1]))
                {
                    before[changed[i + 1]] = expression[changed[i + 1]] + offset;
                    after[changed[i + 1]] = expression[changed[i + 1]] + offset;
                }
                else if (i - 1 >= 0 && isalpha(changed[i - 1]))
                {
                    before[changed[i - 1]] = expression[changed[i - 1]];
                    after[changed[i - 1]] = expression[changed[i - 1]] + offset;
                }
                
                changed[i] = ' ';
            }
        }

        for (int i = changed.length() - 1; i >= 0; i--)
            if (isblank(changed[i]))
                changed.erase(changed.begin() + i);
                        
        for (int i = 0; i < changed.length(); i++)
            if (isalpha(changed[i]) && before.find(changed[i]) == before.end())
            {
                before[changed[i]] = expression[changed[i]];
                after[changed[i]] = expression[changed[i]];
            }
              
        int value = 0;
        for (int i = 0; i < changed.length(); i++)
            if (isalpha(changed[i]))
            {
                if (i == 0) value += before[changed[i]];
                else value += (changed[i - 1] == '+' ? before[changed[i]] : -before[changed[i]]);
            }
               
        cout << "Expression: " << line << endl;
        cout << "    value = " << value << endl;
        for (auto pair : after)
            cout << "    " << pair.first << " = " << pair.second << endl;
    }
    
	return 0;
}
