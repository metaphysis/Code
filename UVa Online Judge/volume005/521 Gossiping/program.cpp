// Gossiping
// UVa ID: 521
// Verdict: Accepted
// Submission Date: 2017-05-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct driver
{
    int line, start;
};

vector<vector<int>> busLines(40, vector <int>());
driver drivers[40];
bool connected[40][40];
int n, d, s, si, di;

bool exchanged(int a, int b)
{
    if (a == b) return true;

    int aline = drivers[a].line, bline = drivers[b].line;
    int total = busLines[aline].size() * busLines[bline].size();

    vector<int> s1;
    while (s1.size() < total)
    {
        for (int i = drivers[a].start; i < busLines[aline].size(); i++)
            s1.push_back(busLines[aline][i]);
        for (int i = 0; i < drivers[a].start; i++)
            s1.push_back(busLines[aline][i]);
    }

    vector<int> s2;
    while (s2.size() < total)
    {
        for (int i = drivers[b].start; i < busLines[bline].size(); i++)
            s2.push_back(busLines[bline][i]);
        for (int i = 0; i < drivers[b].start; i++)
            s2.push_back(busLines[bline][i]);
    }

    for (int i = 0; i < total; i++)
        if (s1[i] == s2[i])
            return true;

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    istringstream iss;
    string line;

    while (getline(cin, line))
    {
        iss.clear(); iss.str(line);
        iss >> n >> d >> s;

        if (n == 0) break;

        memset(connected, false, sizeof(connected));

        for (int i = 1; i <= n; i++)
        {
            busLines[i].clear();

            getline(cin, line); iss.clear(); iss.str(line);
            while (iss >> si) busLines[i].push_back(si);

            getline(cin, line); iss.clear(); iss.str(line);
            while (iss >> si >> di)
            {
                for (int j = 0; j < busLines[i].size(); j++)
                    if (si == busLines[i][j])
                    {
                        drivers[di] = driver{i, j};
                        break;
                    }
            }
        }

        for (int i = 1; i <= d; i++)
            for (int j = i; j <= d; j++)
                connected[i][j] = connected[j][i] = exchanged(i, j);

        for (int k = 1; k <= d; k++)
            for (int i = 1; i <= d; i++)
                for (int j = 1; j <= d; j++)
                    if (connected[i][k] && connected[k][j])
                        connected[i][j] = connected[j][i] = true;

        bool allConnected = true;
        for (int i = 1; i <= d; i++)
            if (!connected[1][i])
            {
                allConnected = false;
                break;
            }

        cout << (allConnected ? "Yes" : "No") << '\n';
    }

    return 0;
}
