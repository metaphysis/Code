// Head Judge Headache
// UVa ID: 790
// Verdict: Accepted
// Submission Date: 2018-01-11
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct team
{
    int tid, solved[8], rejected[8], consumed[8], totalT, totalP, appeared;
    bool operator<(const team &t) const
    {
        if (appeared != t.appeared) return appeared > t.appeared;
        if (totalP != t.totalP) return totalP > t.totalP;
        if (totalT != t.totalT) return totalT < t.totalT;
        return tid < t.tid;
    }
}teams[32];

struct record
{
    int tid, pid, hh, mm, solved, elapsed;
    bool operator < (const record &l) const
    {
        if (elapsed != l.elapsed) return elapsed < l.elapsed;
        return solved < l.solved;
    }
}records[10240];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, tid, pid, hh, mm, solved, maxTeamId, recordCnt;
    char pletter, separator, status;
    istringstream iss;
    string line;

    cin >> cases;

    cin.ignore(1024, '\n');
    getline(cin, line);

    for (int C = 1; C <= cases; C++)
    {
        memset(teams, 0, sizeof(teams));

        for (int i = 0; i < 25; i++)
            teams[i].tid = i + 1;

        maxTeamId = -1;
        recordCnt = 0;

        while (getline(cin, line))
        {
            if (line.length() == 0) break;
            iss.clear(); iss.str(line);
            iss >> tid >> pletter >> hh >> separator >> mm >> status;
            records[recordCnt++] = record{tid - 1, pletter - 'A', hh, mm, status == 'Y' ? 1 : 0, hh * 60 + mm};
        }

        sort(records, records + recordCnt);

        for (int i = 0; i < recordCnt; i++)
        {
            tid = records[i].tid, pid = records[i].pid, hh = records[i].hh, mm = records[i].mm, solved = records[i].solved;
            maxTeamId = max(maxTeamId, tid);

            if (teams[tid].solved[pid]) continue;
            else
            {
                if (!solved) teams[tid].rejected[pid]++;
                else
                {
                    teams[tid].solved[pid] = 1;
                    teams[tid].totalP++;
                    teams[tid].consumed[pid] = hh * 60 + mm + 20 * teams[tid].rejected[pid];
                }
            }
        }

        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 7; j++)
                teams[i].totalT += teams[i].consumed[j];
        
        for (int i = 0; i <= maxTeamId; i++)
            teams[i].appeared = 1;

        sort(teams, teams + 25);
        
        if (C > 1) cout << '\n';

        cout << "RANK TEAM PRO/SOLVED TIME\n";
        for (int i = 0, showRank = 1, trueRank = 1; i < 25; i++, trueRank++)
        {
            if (!teams[i].appeared) break;
            if (i)
            {
                if (teams[i].totalP != teams[i - 1].totalP || teams[i].totalT != teams[i - 1].totalT)
                    showRank = trueRank;
            }

            cout << setw(4) << right << showRank;
            cout << setw(5) << right << teams[i].tid;
            if (teams[i].totalP)
            {
                cout << setw(5) << right << teams[i].totalP;
                cout << setw(11) << right << teams[i].totalT;
            }
            cout << '\n';
        }
    }

    return 0;
}
