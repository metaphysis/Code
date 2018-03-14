// Nesting a Bunch of Brackets
// UVa ID: 551
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char left_brackets[4] = {'(', '[', '{', '<'}, right_brackets[4] = {')', ']', '}', '>'};
    
    string line;
    while (getline(cin, line))
    {
        stack<char> brackets;
        int i = 0, length = line.length(), counter = 0;
        bool error = false;
        
        while (i < length)
        {
            counter++;
            if (line[i] == '(')
            {
                if (i + 1 < length && line[i + 1] == '*')
                {
                    brackets.push('$');
                    i++;
                }
                else
                    brackets.push('(');
            }
            else if (line[i] == '*')
            {
                if (i + 1 < length && line[i + 1] == ')')
                {
                    if (brackets.empty() || brackets.top() != '$')
                    {
                        error = true;
                        break;
                    }
                    else
                    {
                        brackets.pop();
                        i++;
                    }
                }
            }
            else
            {
                bool updated = false;
                for (int j = 0; j < 4; j++)
                    if (left_brackets[j] == line[i])
                    {
                        brackets.push(line[i]);
                        updated = true;
                        break;
                    }
                
                if (!updated)
                {
                    for (int j = 0; j < 4; j++)
                        if (right_brackets[j] == line[i])
                        {
                            if (brackets.empty() || brackets.top() != left_brackets[j])
                                error = true;
                            else
                                brackets.pop();
                            
                            break;
                        }
                }
                
                if (error)
                    break;
            }
            
            i++;
        }
        
        if (brackets.size() > 0)
            error = true;
            
        if (error && i == length)
            counter++;
            
        if (error)
            cout << "NO " << counter << '\n';
        else
            cout << "YES\n";
    }
    
	return 0;
}
