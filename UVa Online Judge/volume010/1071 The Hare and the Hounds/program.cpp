#include <bits/stdc++.h>
using namespace std;

const int maxN = 105;
const int inf = 1000000000;

int caseId, ncp, nroad, ncm, confdist, startIs, endIs, startDir, i, j, k;
bool visit[360], choice[maxN];
int route[1005], path[1005];
int marker[maxN][360], otherIs[maxN][360], otherDir[maxN][360], roadId[maxN][360], roadLen[maxN][360];
int hareLen, houndLen, total, pathCnt;

bool initCase() {
    int x, y, dirX, dirY, len;
    ++caseId;
    cin >> ncp >> nroad >> ncm >> confdist >> startIs >> endIs >> startDir;
    if (startIs == 0) return false;
    memset(choice, 0, sizeof(choice));
    for (i = 1; i <= ncp; ++i) {
        cin >> x;
        choice[x] = true;
    }
    memset(roadId, 0, sizeof(roadId));
    for (i = 1; i <= nroad; ++i) {
        cin >> x >> y >> dirX >> dirY >> len;
        roadId[x][dirX] = i;
        roadLen[x][dirX] = len;
        otherIs[x][dirX] = y;
        otherDir[x][dirX] = dirY;
        roadId[y][dirY] = i;
        roadLen[y][dirY] = len;
        otherIs[y][dirY] = x;
        otherDir[y][dirY] = dirX;
    }
    for (i = 0; i < maxN; ++i)
        for (j = 0; j < 360; ++j)
            marker[i][j] = inf;
    for (i = 1; i <= ncm; ++i) {
        cin >> x >> y >> len;
        for (j = 0; j <= 359; ++j)
            if (roadId[x][j] == y) {
                if (len < marker[x][j]) marker[x][j] = len;
                if (roadLen[x][j] - len < marker[otherIs[x][j]][otherDir[x][j]]) marker[otherIs[x][j]][otherDir[x][j]] = roadLen[x][j] - len;
            }
    }
    return true;
}

bool findPath(int &isect, int &dir, int &dist) {
    int v, vdir, pre;
    dist = 0;
    pathCnt = 0;
    v = isect;
    vdir = dir;
    while (true) {
        path[++pathCnt] = roadId[v][vdir];
        if (marker[v][vdir] + dist <= confdist) {
            isect = otherIs[v][vdir];
            dir = (otherDir[v][vdir] + 180) % 360;
            dist += roadLen[v][vdir];
            return true;
        }
        if (roadLen[v][vdir] + dist > confdist) {
            dist = confdist;
            return false;
        }
        dist += roadLen[v][vdir];
        pre = vdir;
        vdir = (otherDir[v][vdir] + 180) % 360;
        v = otherIs[v][pre];
        if (choice[v]) return false;
        for (i = 0; i <= 180; ++i) {
            if (i == 180) return false;
            j = (vdir + i) % 360;
            if (roadId[v][j] > 0) {
                vdir = j;
                break;
            }
            j = (vdir + 360 - i) % 360;
            if (roadId[v][j] > 0) {
                vdir = j;
                break;
            }
        }
    }
}

void work() {
    int v, vdir, delta;
    k = startIs;
    vdir = startDir;
    hareLen = houndLen = total = 0;
    do {
        if (choice[k]) {
            memset(visit, 0, sizeof(visit));
            visit[(vdir + 180) % 360] = true;
            while (true) {
                v = -1;
                for (i = 0; i <= 180; ++i) {
                    j = (vdir + i) % 360;
                    if (roadId[k][j] > 0 && !visit[j]) {
                        v = j;
                        break;
                    }
                    j = (vdir + 360 - i) % 360;
                    if (roadId[k][j] > 0 && !visit[j]) {
                        v = j;
                        break;
                    }
                }
                visit[v] = true;
                if (findPath(k, v, delta)) {
                    hareLen += delta;
                    houndLen += delta;
                    for (i = 1; i <= pathCnt; ++i)
                        route[++total] = path[i];
                    vdir = v;
                    break;
                } else {
                    vdir = (v + 180) % 360;
                    houndLen += delta * 2;
                }
            }
        } else {
            for (i = 0; i <= 180; ++i) {
                j = (vdir + i) % 360;
                if (roadId[k][j] > 0) {
                    hareLen += roadLen[k][j];
                    houndLen += roadLen[k][j];
                    route[++total] = roadId[k][j];
                    vdir = (otherDir[k][j] + 180) % 360;
                    k = otherIs[k][j];
                    break;
                }
                j = (vdir + 360 - i) % 360;
                if (roadId[k][j] > 0) {
                    hareLen += roadLen[k][j];
                    houndLen += roadLen[k][j];
                    route[++total] = roadId[k][j];
                    vdir = (otherDir[k][j] + 180) % 360;
                    k = otherIs[k][j];
                    break;
                }
            }
        }
    } while (k != endIs);
    cout << "Case " << caseId << ":\n";
    cout << "   Length of hare's route is " << hareLen << "\n";
    cout << "   Length of hound's search is " << houndLen << "\n";
    cout << "   Route:";
    for (i = 1; i <= total; ++i)
        cout << ' ' << route[i];
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (initCase()) work();
    return 0;
}
