// Indexing Web Pages
// UVa ID: 368
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<string> visited;
vector<string> pages;
map<string, set<string>> words;
queue<string> q;
string filename, line, content;

void tolower(string &s)
{
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
}

void process()
{
    int i = 0;
    while (i < content.length())
    {
        if (content[i] == '<')
        {
            i++;
            string block;
            while (i < content.length() && content[i] != '>')
            {
                block += content[i];
                i++;
            }
            if (block.length() > 13)
            {
                if (block.substr(0, 8) == "A HREF=\"" && block.back() == '"')
                {
                    string page = block.substr(8, block.length() - 9);
                    if (visited.find(page) == visited.end())
                    {
                        visited.insert(page);
                        pages.push_back(page);
                        q.push(page);
                    }
                }
            }
        }
        else if (isalpha(content[i]))
        {
            string w;
            while (i < content.length() && isalpha(content[i]))
            {
                w += content[i];
                i++;
            }
            tolower(w);
            words[filename].insert(w);
        }
        else i++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    visited.insert("index.htm");
    pages.push_back("index.htm");
    q.push("index.htm");
    while (!q.empty())
    {
        filename = q.front(); q.pop();
        content.clear();
        while (getline(cin, line), line.length() > 0)
        {
            content += line;
            content += '\n';
        }
        process();
    }

    string w;
    int cases = 0;
    while (cin >> w)
    {
        if (cases++) cout << '\n';
        cout << '"' << w << '"';
        vector<string> lists;
        tolower(w);
        for (auto fs : pages)
        {
            if (words[fs].find(w) != words[fs].end())
                lists.push_back(fs);
        }
        if (lists.size() == 0) cout << " can not be found in any page.\n";
        else
        {
            cout << " can be found in the following pages:\n";
            for (auto ls : lists)
                cout << "     " << ls << '\n';
        }
    }

    return 0;
}
