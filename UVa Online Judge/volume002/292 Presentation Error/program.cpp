// Presentation Error
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> En;
string jury, submit;

void removeTrailingEmptyLines(string &s)
{
    while (s.length() >= 2 && s[s.length() - 1] == '\n' && s[s.length() - 2] == '\n')
        s.pop_back();
}

void toUpper(string &s)
{
    for (int i = 0; i < s.length(); i++)
        if (isalpha(s[i]))
            s[i] = (char)(toupper(s[i]));
}

void addEssential(string &s)
{
    int idx = 0;
    while (idx < s.length())
    {
        if (s[idx] == '[')
        {
            idx++;
            string block;
            while (s[idx] != ']')
            {
                block += s[idx];
                idx++;
            }
            toUpper(block);
            En.push_back(block);
        }
        idx++;
    }
}

bool dfs(int i, int j)
{
    if (j == En.size()) return true;
    int idx = i;
    while (idx < submit.length())
    {
        idx = submit.find(En[j], idx);
        if (idx != submit.npos)
        {
            idx += En[j].length();
            if (dfs(idx, j + 1)) return true;
        } 
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    int cases, n1, n2;
    string line;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n1 >> n2;
        cin.ignore(256, '\n');

        jury.clear(), submit.clear(), En.clear();
        for (int i = 1; i <= n1; i++)
        {
            getline(cin, line);
            addEssential(line);
            while (line.length() > 0 && isblank(line.back())) line.pop_back();
            jury += line;
            jury += '\n';
        }

        for (int i = 1; i <= n2; i++)
        {
            getline(cin, line);
            while (line.length() > 0 && isblank(line.back())) line.pop_back();
            submit += line;
            submit += '\n';
        }

        removeTrailingEmptyLines(jury);
        removeTrailingEmptyLines(submit);

        if (jury == submit)
        {
            cout << "Accepted\n";
            continue;
        }
        
        toUpper(submit);

        if (dfs(0, 0)) cout << "Presentation Error\n";
        else cout << "Wrong Answer\n";
    }
    
	return 0;
}
