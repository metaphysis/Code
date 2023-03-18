// The Ultimate Bamboo Eater
// UVa ID: 12074
// Verdict: Accepted
// Submission Date: 2023-03-18
// UVa Run Time: 0.370s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)

const int MAXN = 100010;

struct LAND {
    int xi, yi, wi, li;
    bool operator<(const LAND ld) const { return wi < ld.wi; }
} lands[MAXN];

int n;
int xr[MAXN << 2], yr[MAXN << 4], cnt, lc[MAXN << 4], rc[MAXN << 4];
int X[MAXN << 3], xc, Y[MAXN << 3], yc;

void build() {
    cnt = 0;
    memset(xr, 0, sizeof xr);
    memset(yr, 0, sizeof yr);
}

void updateY(int &py, int ly, int ry, int x, int y, int value) {
    if (!py) {
        py = ++cnt;
        lc[py] = rc[py] = yr[py] = 0;
    }
    if (ly == ry) yr[py] = max(yr[py], value);
    else {
        int my = (ly + ry) >> 1;
        if (y <= my)
            updateY(lc[py], ly, my, x, y, value);
        else
            updateY(rc[py], my + 1, ry, x, y, value);
        yr[py] = max(yr[lc[py]], yr[rc[py]]);
    }
}

void updateX(int px, int lx, int rx, int x, int y, int value) {
    if (lx != rx) {
        int mx = (lx + rx) >> 1;
        if (x <= mx)
            updateX(LC(px), lx, mx, x, y, value);
        else
            updateX(RC(px), mx + 1, rx, x, y, value);
    }
    updateY(xr[px], 0, yc - 1, x, y, value);
}

int queryY(int &py, int ly, int ry, int qly, int qry) {
    if (!py) return 0;
    if (ly > qry || ry < qly) return 0;
    if (qly <= ly && ry <= qry) return yr[py];
    int my = (ly + ry) >> 1;
    int q1 = queryY(lc[py], ly, my, qly, qry);
    int q2 = queryY(rc[py], my + 1, ry, qly, qry);
    return max(q1, q2);
}

int queryX(int px, int lx, int rx, int qlx, int qly, int qrx, int qry) {
    if (lx > qrx || rx < qlx) return 0;
    if (qlx <= lx && rx <= qrx) return queryY(xr[px], 0, yc - 1, qly, qry);
    int mx = (lx + rx) >> 1;
    int q1 = queryX(LC(px), lx, mx, qlx, qly, qrx, qry);
    int q2 = queryX(RC(px), mx + 1, rx, qlx, qly, qrx, qry);
    return max(q1, q2);
}

int getId(int *a, int c, int v) { return lower_bound(a, a + c, v) - a; }

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> n;
        xc = yc = 0;
        for (int i = 0, xi, yi; i < n; i++) {
            cin >> xi >> yi >> lands[i].wi >> lands[i].li;
            lands[i].xi = xi - yi, lands[i].yi = xi + yi;
            X[xc++] = lands[i].xi, Y[yc++] = lands[i].yi;
            X[xc++] = lands[i].xi - lands[i].li, Y[yc++] = lands[i].yi - lands[i].li;
            X[xc++] = lands[i].xi + lands[i].li, Y[yc++] = lands[i].yi + lands[i].li;
        }
        sort(X, X + xc);
        sort(Y, Y + yc);
        xc = unique(X, X + xc) - X;
        yc = unique(Y, Y + yc) - Y;
        sort(lands, lands + n);
        int m = 0, tmp;
        build();
        for (int i = 0; i < n; i++) {
            tmp = queryX(1, 0, xc - 1, getId(X, xc, lands[i].xi - lands[i].li), 
                getId(Y, yc, lands[i].yi - lands[i].li), getId(X, xc, lands[i].xi + lands[i].li),
                getId(Y, yc, lands[i].yi + lands[i].li)) + 1;
            m = max(m, tmp);
            updateX(1, 0, xc - 1, getId(X, xc, lands[i].xi), getId(Y, yc, lands[i].yi), tmp);
        }
        cout << m << '\n';
    }
    return 0;
}
