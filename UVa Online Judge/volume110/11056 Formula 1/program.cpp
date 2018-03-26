// Formula 1
// UVa ID: 11056
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct pilot
{
    string name1, name2;
    int ms;
    
    bool operator<(const pilot &p) const
    {
        if (ms != p.ms) return ms < p.ms;
        return name2 < p.name2;
    }
};

pilot parse(string line)
{
    istringstream iss(line);

    string useless;
    int min = 0, sec = 0, ms = 0;
    pilot p;
    iss >> p.name1 >> useless;
    iss >> min >> useless;
    iss >> sec >> useless;
    iss >> ms;
    p.name2 = p.name1;
    for (int i = 0; i < p.name2.length(); i++)
        p.name2[i] = tolower(p.name2[i]);
    p.ms = min * 60 * 1000 + sec * 1000 + ms;

    return p;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string line;

    while (cin >> n)
    {
        cin.ignore(1024, '\n');
        
        vector<pilot> pilots;
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            pilots.push_back(parse(line));
        }
        sort(pilots.begin(), pilots.end());

        int row = 1, lastTime = -1;
        for (int i = 0; i < pilots.size(); i++)
        {
            if (i % 2 == 0)
                cout << "Row " << row++ << '\n';
            cout << pilots[i].name1 << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
