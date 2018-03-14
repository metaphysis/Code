// My Dear Neighbours
// UVa ID: 10928
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct neighbour
{
    int idx, cnt;
    bool operator<(const neighbour &nr) const
    {
        if (cnt != nr.cnt) return cnt < nr.cnt;
        return idx < nr.idx;
    }
}neighbours[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int P;
        cin >> P; cin.ignore(1024, '\n');
        string line;
        for (int i = 0; i < P; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            int room, cnt = 0;
            while (iss >> room) cnt++;
            neighbours[i].idx = i + 1;
            neighbours[i].cnt = cnt;
        }
        sort(neighbours, neighbours + P);
        cout << neighbours[0].idx;
        for (int i = 1; i < P; i++)
            if (neighbours[i].cnt == neighbours[0].cnt)
                cout << ' ' << neighbours[i].idx;
            else break;
        cout << '\n';
    }

    return 0;
}
