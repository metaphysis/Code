// Stats
// UVa ID: 570
// Verdict: Accepted
// Submission Date: 2017-05-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct player
{
    int games, hit, kill, err, block, dig;
};

map<string, player> record;

void report()
{
    cout.setf(ios::fixed);
    cout.precision(3);

    cout << "Player  Hit Pct    KPG      BPG      DPG\n";
    cout << "-----------------------------------------\n";

    for (auto r : record)
    {
        cout << setw(4) << left << r.first;

        if (r.second.hit == 0)
            cout << setw(10) << right << "+0.000";
        else
        {
            stringstream ss;
            string output;

            int kill = r.second.kill - r.second.err;
 
            if (kill >= 0) ss << '+';
            ss << fixed << setprecision(3) << (double)(kill) / r.second.hit;
            
            ss >> output;
            cout << setw(10) << right << output;
        }

        if (r.second.games > 0)
        {
            cout << setw(9) << right << (double)(r.second.kill) / r.second.games;
            cout << setw(9) << right << (double)(r.second.block) / r.second.games;
            cout << setw(9) << right << (double)(r.second.dig) / r.second.games;
        }
        else
        {
            cout << setw(9) << right << "0.000";
            cout << setw(9) << right << "0.000";
            cout << setw(9) << right << "0.000";
        }

        cout << '\n';
    }

    cout << '\n';

    record.clear();
}

void checkin()
{
    string numberOfPlayers, playerId;

    cin >> numberOfPlayers;
    int np = stoi(numberOfPlayers);
    
    for (int i = 1; i <= np; i++)
    {
        cin >> playerId;
        if (record.find(playerId) == record.end())
            record[playerId] = player{0, 0, 0, 0, 0, 0};
        record[playerId].games++;
    }
    
    if (record.find("team") == record.end())
        record["team"] = player{0, 0, 0, 0, 0, 0};
    record["team"].games++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char play;
    string playerId;

    while (cin >> play)
    {
        if (play == 'R') { report(); continue; }
        if (play == 'C') { checkin(); continue; }

        cin >> playerId;
        switch (play)
        {
            case 'H':
                record[playerId].hit++, record["team"].hit++;
                break;
            case 'K':
                record[playerId].kill++, record[playerId].hit++;
                record["team"].kill++, record["team"].hit++;
                break;
            case 'E':
                record[playerId].err++, record[playerId].hit++;
                record["team"].err++, record["team"].hit++;
                break;
            case 'B':
                record[playerId].block++, record["team"].block++;
                break;
            case 'D':
                record[playerId].dig++, record["team"].dig++;
                break;
        }
    }
    
    return 0;
}
