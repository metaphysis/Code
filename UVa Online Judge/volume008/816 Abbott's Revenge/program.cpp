// Abbott's Revenge
// UVa ID: 816
// Verdict: Accepted
// Submission Date: 2016-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, int> direction = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
map<char, int> turn = {{'L', 0}, {'F', 1}, {'R', 2}};

struct package
{
    int r, c, d;
    vector<pair<int, int>> walk;
};

bool flag = false;
char startd;
string maze, sign;
int startr, startc, endr, endc, somer, somec;
int visited[10][10][4], successor[10][10][4][4], record[1000][2];
int forward[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int offset[4][3][3] = {
    {{0, -1, 3}, {-1, 0, 0}, {0, 1, 1}}, {{-1, 0, 0}, {0, 1, 1}, {1, 0, 2}},
    {{0, 1, 1}, {1, 0, 2}, {0, -1, 3}}, {{1, 0, 2}, {0, -1, 3}, {-1, 0, 0}}
};

bool bfs()
{
    vector<pair<int, int>> startwalk = {{startr, startc}};
    startr += forward[direction[startd]][0], startc += forward[direction[startd]][1];
    package start = (package){startr, startc, direction[startd], startwalk};

    memset(visited, 0, sizeof(visited));
    queue<package> unvisited; unvisited.push(start);
    
    while (unvisited.empty() == false)
    {
        package current = unvisited.front();
        unvisited.pop();

        int r = current.r, c = current.c, d = current.d;
        current.walk.push_back(make_pair(r, c));

        if (r == endr && c == endc)
        {
            for (int i = 0; i < current.walk.size(); i++)
            {
                if (i % 10 == 0) cout << ' ';
                cout << " (" << current.walk[i].first << ',' << current.walk[i].second << ')';
                if ((i + 1) % 10 == 0) cout << '\n';
            }
            if (current.walk.size() % 10 != 0) cout << '\n';

            return true;
        }

        visited[r][c][d] = 1;
        for (int i = 0; i < 3; i++)
            if (successor[r][c][d][i])
            {
                int nextr = r + offset[d][i][0], nextc = c + offset[d][i][1], nextd = offset[d][i][2];
                if (visited[nextr][nextc][nextd] == 0)
                    unvisited.push((package){nextr, nextc, nextd, current.walk});
            }
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> maze, maze != "END")
    {
        memset(successor, 0, sizeof(successor));

        cin >> startr >> startc >> startd >> endr >> endc;
 
        while (cin >> somer, somer > 0)
        {
            cin >> somec;
            while (cin >> sign, sign != "*")
            {
                for (int i = 1; i < sign.length(); i++)
                    successor[somer][somec][direction[sign.front()]][turn[sign[i]]] = 1;
            }
        }

        cout << maze << '\n';

        if (!bfs()) cout << "  No Solution Possible\n";
    }

	return 0;
}
