// Argus
// UVa ID: 1203
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct query
{
    int id, seconds, period;
    bool operator<(const query &q) const
    {
        if (seconds != q.seconds) return seconds > q.seconds;
        return id > q.id;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string command;
    int id, period;
    priority_queue<query> q;
    
    while (cin >> command)
    {
        if (command.front() == '#') break;
        cin >> id >> period;
        q.push(query{id, period, period});
    }
    
    int k;
    cin >> k;
    while (k--)
    {
        query qy = q.top(); q.pop();
        cout << qy.id << '\n';
        qy.seconds += qy.period;
        q.push(qy);
    }
    
    return 0;
}
