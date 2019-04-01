// Presentation Error
// UVa ID: 292
// Verdict: Accepted
// Submission Date: 2019-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> En, jury, submit;

void addEssential()
{
    for (auto s : jury)
        for (int i = 0; i < s.length(); i++)
            if (s[i] == '[')
            {
                i++;
                string block;
                while (i < s.length() && s[i] != ']')
                {
                    block += s[i];
                    i++;
                }
                En.push_back(block);
            }
}

bool pe()
{
    string s;
    for (auto e : submit) s += e, s += '\n';
    int i = 0, j = 0;
	while (i < En.size() && j < s.length())
	{
	    j = s.find(En[i], j);
	    if (j == s.npos) return false;
	    j += En[i].length();
	    i++;
	}
	return i == En.size();
}

bool identical()
{
    if (jury.size() != submit.size()) return false;
    for (int k = 0; k < jury.size(); k++)
    {
        string s = jury[k], t = submit[k];
        int i = 0, j = 0;
	    while (i < s.length() && j < t.length())
		    if (s[i] == '[' || s[i] == ']') i++;
		    else if (s[i] == t[j]) i++, j++;
		    else return false;
	    if (i < s.length() && s[i] == ']') i++;
	    if (i != s.length() || j != t.length()) return false;
	}
	return true;
}

void trim(vector<string> &vs)
{
    for (int i = vs.size() - 1; i >= 0; i--)
        if (vs[i].length() == 0)
            vs.pop_back();
        else
            break;
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

        jury.clear(), submit.clear();
        for (int i = 1; i <= n1; i++)
        {
            getline(cin, line);
            while (line.length() > 0 && isspace(line.back())) line.pop_back();
            jury.push_back(line);
        }
        for (int i = 1; i <= n2; i++)
        {
            getline(cin, line);
            while (line.length() > 0 && isspace(line.back())) line.pop_back();
            submit.push_back(line);
        }

        trim(jury);
        trim(submit);

        if (identical())
        {
            cout << "Accepted\n";
            continue;
        }

        for (auto &e : jury)
            for (auto &c : e)
                if (isalpha(c))
                    c = toupper(c);
        for (auto &e : submit)
            for (auto &c : e)
                if (isalpha(c))
                    c = toupper(c);

        En.clear();
        addEssential();

        if (pe()) cout << "Presentation Error\n";
        else cout << "Wrong Answer\n";
    }

	return 0;
}
