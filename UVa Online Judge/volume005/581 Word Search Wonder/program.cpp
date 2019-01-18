// Word Search Wonder
// UVa ID: 581
// Verdict: Accepted
// Submission Date: 2019-01-18
// UVa Run Time: 0.710s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> words;
vector<vector<char>> grid;

int s;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
string orientation[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

int search(int x, int y, int wi)
{
    for (int d = 0; d < 8; d++)
    {
        int xx = x, yy = y;
        bool same = true;
        for (int i = 0; i < words[wi].size(); i++)
        {
            if (xx < 0 || xx >= s || yy < 0 || yy >= grid[xx].size())
            {
                same = false;
                break;
            }
            if (grid[xx][yy] != words[wi][i])
            {
                same = false;
                break;
            }
            xx += dx[d], yy += dy[d];
        }
        if (same) return d;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string word, line;
    int cases, m, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';

        cin >> s;
        if (s <= 0)
        {
            cin >> m;
            for (int i = 0; i < m; i++)
            {
                cin >> word;
                cout << word << " NOT FOUND\n";
            }
            cin >> n;
            cin.ignore(256, '\n');
            for (int i = 0; i < n; i++)
                getline(cin, line);
            continue;
        }

        words.clear();
        grid.assign(s, vector<char>());

        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> word;
            words.push_back(word);
        }
        
        cin >> n;
        cin.ignore(256, '\n');
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            for (auto c : line)
                if (isalpha(c))
                {
                    grid[cnt % s].push_back(toupper(c));
                    cnt++;
                }
        }

        int d;
        for (int i = 0; i < words.size(); i++)
        {
            cout << words[i] << ' ';
            bool found = false;
            for (int j = 0; j < cnt; j++)
            {
                int x = j % s, y = j / s;
                if ((d = search(x, y, i)) >= 0)
                {
                    cout << j << ' ' << orientation[d] << '\n';
                    found = true;
                    break;
                }
            }
            if (!found) cout << "NOT FOUND\n";
        }
    }

    return 0;
}
