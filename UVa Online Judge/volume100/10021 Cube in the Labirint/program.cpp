// Cube in the Labirint
// UVa ID: 10021
// Verdict: Accepted
// Submission Date: 2023-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int turn(int s, int k) {
    int b1 = s / 100000, b2 = (s % 100000) / 10000, b3 = (s % 10000) / 1000;
    int b4 = (s % 1000) / 100, b5 = (s % 100) / 10, b6 = s % 10;
    if (k == 0) return b4 * 100000 + b3 * 10000 + b1 * 1000 + b2 * 100 + b5 * 10 + b6;
    if (k == 1) return b3 * 100000 + b4 * 10000 + b2 * 1000 + b1 * 100 + b5 * 10 + b6;
    if (k == 2) return b6 * 100000 + b5 * 10000 + b3 * 1000 + b4 * 100 + b1 * 10 + b2;
    if (k == 3) return b5 * 100000 + b6 * 10000 + b3 * 1000 + b4 * 100 + b2 * 10 + b1;
}

map<int, int> id;

int getId(int s) {
    if (id.count(s)) return id[s];
    return id[s] = id.size();
}

int visited[11][11][1010];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int d[11][11][7], b[11][11][4];
    int X, Y, A, B, C, D;
    istringstream iss;
    string line;
    cin >> T;
    for (int cs = 0; cs < T; cs++) {
        if (cs) cout << '\n';
        memset(d, 0x3f, sizeof d);
        memset(b, 0, sizeof b);
        memset(visited, 0, sizeof visited);
        cin >> X >> Y >> A >> B >> C >> D;
        cin.ignore(256, '\n');
        getline(cin, line);
        while (true) {
            if (line.length() == 0) break;
            if (line == "v") {
                while (getline(cin, line)) {
                    if (line == "h" || line == "v" || line.length() == 0) break;
                    iss.clear();
                    iss.str(line);
                    int x, y;
                    iss >> x >> y;
                    b[x][y][1] = b[x + 1][y][0] = 1;
                }
            } else if (line == "h") {
                while (getline(cin, line)) {
                    if (line == "v" || line == "h" || line.length() == 0) break;
                    iss.clear();
                    iss.str(line);
                    int x, y;
                    iss >> x >> y;
                    b[x][y][3] = b[x][y + 1][2] = 1;
                }
            }
        }
        
        d[A][B][1] = 0;
        visited[A][B][getId(123456)] = 1;
        queue<tuple<int, int, int, int>> q;
        q.push(make_tuple(A, B, 123456, 0));
        while (!q.empty()) {
            tuple<int, int, int, int> t = q.front();
            q.pop();
            int x = get<0>(t), y = get<1>(t), f = get<2>(t), s = get<3>(t);
            for (int k = 0; k < 4; k++) {
                if (b[x][y][k]) continue;
                int nx = x + offset[k][0], ny = y + offset[k][1];
                if (nx < 1 || nx > X || ny < 1 || ny > Y) continue;
                int ff = turn(f, k);
                if (visited[nx][ny][getId(ff)]) continue;
                visited[nx][ny][getId(ff)] = 1;
                if (d[nx][ny][ff / 100000] > s + 1)
                    d[nx][ny][ff / 100000] = s + 1;
                q.push(make_tuple(nx, ny, ff, s + 1));
            }
        }
        if (d[C][D][1] != 0x3f3f3f3f) cout << d[C][D][1] << '\n';
        else cout << "No solution\n";
    }
    return 0;
}
