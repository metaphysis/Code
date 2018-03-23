// Team Arrangement
// UVa ID: 1219
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int G = 0, D = 1, M = 2, S = 3;

string roleText = "GDMS";
map<char, int> roleIdx = {{'G', 0}, {'D', 1}, {'M', 2}, {'S', 3}};

struct player
{
    string name;
    int number, role, record;

    bool operator<(const player &p) const
    {
        return number < p.number;
    }
};

bool cmpCaptain(player p1, player p2)
{
    if (p1.record != p2.record)
        return p1.record > p2.record;
    return p1.number > p2.number;
}

bool cmpMember(player p1, player p2)
{
    if (p1.role != p2.role)
        return p1.role < p2.role;
    return p1.number < p2.number;
}

player parse(string line)
{ 
    player aPlayer;

    char letter;
    istringstream iss(line);
    iss >> aPlayer.number >> aPlayer.name >> letter;
    aPlayer.role = roleIdx[letter];

    int year[10000] = {0}, start, end;
    while (iss >> start >> letter >> end)
    {
        for (int i = start; i <= end; i++)
            year[i] = 1;
    }
    aPlayer.record = count(year, year + 10000, 1);

    return aPlayer;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    vector<player> players;

    while (getline(cin, line))
    {
        if (line == "0") break;
        players.clear();
        players.push_back(parse(line));
        for (int i = 2; i <= 22; i++)
        {
            getline(cin, line);
            players.push_back(parse(line));
        }
        sort(players.begin(), players.end());

        getline(cin, line);
        istringstream iss(line);

        char dash;
        int defenders, midfielders, strikers, goalkeepers = 1;
        iss >> defenders >> dash >> midfielders >> dash >> strikers;
        
        vector<player> team;
        int dcnt = 0, mcnt = 0, scnt = 0, gcnt = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (dcnt < defenders && players[i].role == D)
            {
                team.push_back(players[i]);
                dcnt++;
            }
            if (mcnt < midfielders && players[i].role == M)
            {
                team.push_back(players[i]);
                mcnt++;
            }
            if (scnt < strikers && players[i].role == S)
            {
                team.push_back(players[i]);
                scnt++;
            }
            if (gcnt < goalkeepers && players[i].role == G)
            {
                team.push_back(players[i]);
                gcnt++;
            }
        }
        
        if (dcnt != defenders || mcnt != midfielders || scnt != strikers || gcnt != goalkeepers)
        {
            cout << "IMPOSSIBLE TO ARRANGE\n\n";
            continue;
        }
        
        sort(team.begin(), team.end(), cmpCaptain);
        player captain = team.front();
        cout << captain.number << ' ' << captain.name << ' ' << roleText[captain.role] << '\n';

        team.erase(team.begin());
        sort(team.begin(), team.end(), cmpMember);
        for (auto member : team)
            cout << member.number << ' ' << member.name << ' ' << roleText[member.role] << '\n';
        cout << '\n';
    }

    return 0;
}
