// Knights In FEN
// UVa ID: 10422
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.590s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct state
{
    string config;
    int x, y, moves;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int offset[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    string finals = "111110111100 110000100000";

    cin >> cases;
    cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        string line, config;
        for (int i = 0; i < 5; i++)
        {
            getline(cin, line);
            for (int i = 0; i < 5; i++)
                config += line[i];
        }
        
        int x, y;
        for (int i = 0; i < config.length(); i++)
            if (config[i] == ' ')
            {
                x = i / 5, y = i % 5;
                break;
            }

        queue<state> q;
        q.push(state{config, x, y, 0});
        set<string> visited;
        visited.insert(config);
        
        bool solvable = false;
        while (!q.empty())
        {
            state s = q.front(); q.pop();
            if (s.moves >= 11) continue;
            if (s.config == finals)
            {
                solvable = true;
                cout << "Solvable in " << s.moves << " move(s).\n";
                break;
            }
            for (int k = 0; k < 8; k++)
            {
                int nextx = s.x + offset[k][0];
                int nexty = s.y + offset[k][1];
                if (nextx >= 0 && nextx < 5 && nexty >= 0 && nexty < 5)
                {
                    string nextc(s.config);
                    swap(nextc[s.x * 5 + s.y], nextc[nextx * 5 + nexty]);
                    if (visited.find(nextc) == visited.end())
                    {
                        q.push(state{nextc, nextx, nexty, s.moves + 1});
                        visited.insert(nextc);
                    }
                }
            }
        }
        if (!solvable) cout << "Unsolvable in less than 11 move(s).\n";
    }

    return 0;
}
