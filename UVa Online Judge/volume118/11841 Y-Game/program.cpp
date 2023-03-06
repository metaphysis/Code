// Y-Game
// UVa ID: 11841
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point { int x, y, z; } ps[410];

int n, m;

bool isConnected(int i, int j) {
    if (ps[i].x == ps[j].x && abs(ps[i].y - ps[j].y) == 1) return true;
    if (ps[i].y == ps[j].y && abs(ps[i].x - ps[j].x) == 1) return true;
    if (ps[i].z == ps[j].z && abs(ps[i].x - ps[j].x) == 1) return true;
    return false;
}

int tag[410], connected[410];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> m, m) {
        int x, y, z;
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> z;
            ps[i] = point{x, y, z};
        }
        int cc = 0;
        int Benny = 0;
        memset(tag, 0, sizeof tag);
        for (int i = 0; i < m; i++) {
            if (!tag[i]) {
                int L = 0, R = 0, B = 0;
                tag[i] = 1;
                L |= ps[i].x == 0;
                R |= ps[i].y == 0;
                B |= ps[i].z == 0;
                cc = 0;
                connected[cc++] = i;
                for (int j = i + 1; j < m; j++) {
                    if (!tag[j])
                        for (int k = 0; k < cc; k++) {
                            if (isConnected(connected[k], j)) {
                                tag[j] = 1;
                                connected[cc++] = j;
                                L |= ps[j].x == 0;
                                R |= ps[j].y == 0;
                                B |= ps[j].z == 0;
                                break;
                            }
                        }
                }
                if (L && R && B) {
                    Benny = 1;
                    break;
                }
            }
        }
        cout << (Benny ? "Benny" : "Willy") << '\n';
    }
    return 0;
}
