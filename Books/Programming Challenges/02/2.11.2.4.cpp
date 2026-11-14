#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)

const int MAXN = 100010;

int cnt;
int xr[MAXN << 2], yr[MAXN << 4], lc[MAXN << 4], rc[MAXN << 4];
int xc, yc;

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
        if (y <= my) updateY(lc[py], ly, my, x, y, value);
        else updateY(rc[py], my + 1, ry, x, y, value);
        yr[py] = max(yr[lc[py]], yr[rc[py]]);
    }
}

void updateX(int px, int lx, int rx, int x, int y, int value) {
    if (lx != rx) {
        int mx = (lx + rx) >> 1;
        if (x <= mx) updateX(LC(px), lx, mx, x, y, value);
        else updateX(RC(px), mx + 1, rx, x, y, value);
    }
    updateY(xr[px], 0, yc - 1, x, y, value);
}
