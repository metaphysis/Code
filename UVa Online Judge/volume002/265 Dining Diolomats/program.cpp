// Dining Diplomats
// UVa ID: 265
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct diplomat
{
    string code;
    int language;
};

vector<diplomat> diplomats;
vector<vector<int>> edges;
bool flag;
vector<bool> seated(10);
vector<int> table(10);
map<string, set<string>> relations;

bool isNext(int i, int j)
{
    // the data set might contain a country ABC that has relations with
    // DEF but DEF doesn't have relations with ABC
    // so they couldn't sit next to each other. -- by brainfry
    bool hasRelation = false;
    if (diplomats[i].code == diplomats[j].code ||
        (relations[diplomats[i].code].count(diplomats[j].code) > 0 &&
            relations[diplomats[j].code].count(diplomats[i].code) > 0))
        hasRelation = true;

    return hasRelation && diplomats[i].language & diplomats[j].language;
}

char getCommonLanguage(int i, int j)
{
    int commonLanguage = diplomats[i].language & diplomats[j].language;

    char language = 'A';
    while ((commonLanguage & 1) == 0)
    {
        language++;
        commonLanguage >>= 1;
    }

    return language;
}

void dfs(int guest, int index)
{
    if (flag)
        return;

    if (index == 10)
    {
        if (count(edges[guest].begin(), edges[guest].end(), 0) > 0)
        {
            flag = true;
            for (int i = 0; i < 10; i++)
            {
                cout << (i + 1);
                cout << " " << getCommonLanguage(table[((i - 1) + 10) % 10], table[i]);
                cout << " " << diplomats[table[i]].code;
                cout << " " << getCommonLanguage(table[i], table[(i + 1) % 10]);
                cout << endl;
            }
        }

        return;
    }
    else
    {
        for (int i = 0; i < edges[guest].size(); i++)
            if (seated[edges[guest][i]] == false)
            {
                seated[edges[guest][i]] = true;
                table[index] = edges[guest][i];

                dfs(edges[guest][i], index + 1);

                if (flag)
                    return;

                seated[edges[guest][i]] = false;
            }
    }
}

void findCircle()
{
    edges.clear();
    edges.assign(10, vector < int >());

    for (int i = 0; i < 10; i++)
        for (int j = i + 1; j < 10; j++)
            if (isNext(i, j))
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }

    flag = false;
    fill(seated.begin(), seated.end(), false);
    table[0] = 0;
    seated[0] = true;

    dfs(0, 1);

    if (flag == false)
        cout << "NO SOLUTION EXISTS" << endl;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line.length() > 0)
        {
            diplomat d;

            string language;
            istringstream iss(line);
            iss >> d.code >> language;

            d.language = 0;
            for (int i = 0; i < language.length(); i++)
                d.language |= 1 << (language[i] - 'A');

            string country;
            while (iss >> country)
                relations[d.code].insert(country);

            diplomats.push_back(d);
        }
        else
        {
            findCircle();
            cout << endl;
            diplomats.clear();
            relations.clear();
        }
    }

    return 0;
}
