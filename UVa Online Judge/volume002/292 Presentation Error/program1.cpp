// Presentation Error
// UVa ID: 292
// Verdict: Accepted
// Submission Date: 2019-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void trim(string &s)
{
    while (s.length() >= 2 && s[s.length() - 1] == '\n' && s[s.length() - 2] == '\n')
        s.pop_back();
    if (s.length() == 1 && s.back() == '\n') s.pop_back();
}

void toUpper(string &s)
{
    for (int i = 0; i < s.length(); i++)
        if (isalpha(s[i]))
            s[i] = toupper(s[i]);
}

void addEssential(vector<string> &En, string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '[')
        {
            i++;
            string block;
            while (i < s.length() && s[i] != ']')
            {
                block += s[i];
                i++;
            }
            toUpper(block);
            En.push_back(block);
        }
    }
}

bool pe(vector<string> &En, string &submit)
{
    int i = 0, j = 0;
	while (i < En.size() && j < submit.length())
	{
	    j = submit.find(En[i], j);
	    if (j == submit.npos) return false;
	    j += En[i].length();
	    i++;
	}
	return i == En.size();
}

bool identical(string &s, string &t)
{
    int i = 0, j = 0;
    while (i < s.length() && j < t.length())
	    if (s[i] == '[' || s[i] == ']') i++;
	    else if (s[i] == t[j]) i++, j++;
	    else return false;
    if (i < s.length() && s[i] == ']') i++;
	return i == s.length() && j == t.length();
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

        vector<string> En;
        string jury, submit;
        for (int i = 1; i <= n1; i++)
        {
            getline(cin, line);
            addEssential(En, line);
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

        trim(jury);
        trim(submit);

        if (identical(jury, submit))
        {
            cout << "Accepted\n";
            continue;
        }
        
        toUpper(submit);

        if (pe(En, submit)) cout << "Presentation Error\n";
        else cout << "Wrong Answer\n";
    }
    
	return 0;
}
