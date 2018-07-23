// Euro Cup 2000
// UVa ID: 10186
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, scores[21], temp[21], win[21], ranks[21][2];
map<string, int> indexer;
string names[21];
vector<pair<int, int>> unplayed;
int tempRank[21] = {};

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

void dfs(int depth)
{
    if (depth == unplayed.size())
    {
        copy(scores, scores + n, temp);
        for (int i = 0; i < depth; i++)
        {
            if (win[i] == 0) temp[unplayed[i].first] += 3;
            else if (win[i] == 1) temp[unplayed[i].second] += 3;
            else
            {
                temp[unplayed[i].first] += 1;
                temp[unplayed[i].second] += 1;
            }
        }

        vector<pair<int, int>> points;
        for (int i = 0; i < n; i++)
            points.push_back(make_pair(i, temp[i]));
        sort(points.begin(), points.end(), cmp);

        int pos = 1;
        tempRank[points[0].first] = pos;
        for (int i = 1; i < n; i++)
        {
            if (points[i].second != points[i - 1].second) pos++;
            tempRank[points[i].first] = pos;
        }
        for (int i = 0; i < n; i++)
        {
            ranks[i][0] = min(ranks[i][0], tempRank[i]);
            ranks[i][1] = max(ranks[i][1], tempRank[i]);
        }
        return;
    }
    for (int i = 0; i <= 2; i++)
    {
        win[depth] = i;
        dfs(depth + 1);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string team, team1, team2;
    int goal1, goal2, cases = 0;
    int g, played[21][21] = {};

    while (cin >> n, n > 0)
    {
        indexer.clear();
        memset(played, 0, sizeof(played));
        memset(scores, 0, sizeof(scores));

        for (int i = 0; i < n; i++)
        {
            cin >> team;
            indexer[team] = i;
            names[i] = team;
        }

        cin >> g;
        for (int i = 0; i < g; i++)
        {
            cin >> team1 >> team2 >> goal1 >> goal2;
            if (goal1 > goal2) scores[indexer[team1]] += 3;
            if (goal1 < goal2) scores[indexer[team2]] += 3;
            if (goal1 == goal2)
            {
                scores[indexer[team1]]++;
                scores[indexer[team2]]++;
            }
            played[indexer[team1]][indexer[team2]] = 1;
        }
        
        unplayed.clear();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!played[i][j])
                    unplayed.push_back(make_pair(i, j));

        for (int i = 0; i < n; i++)
        {
            ranks[i][0] = 0x3f3f3f3f;
            ranks[i][1] = 0;
        }

        dfs(0);

        cout << "Group #" << ++cases << '\n';
        for (int i = 0; i < n; i++)
        {
            cout << names[i] << ' ' << ranks[i][0] << '-' << ranks[i][1] << '\n';
        }
        cout << '\n';
    }

    return 0;
}
