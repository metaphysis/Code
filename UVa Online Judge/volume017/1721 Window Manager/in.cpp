#include <bits/stdc++.h>

using namespace std;

struct window { int x, y, w, h; };

int SW = 100, SH = 100;
vector<window> windows;

bool overlapped(window wid)
{
    for (int i = 0; i < windows.size(); i++)
    {
        int x1 = max(wid.x, windows[i].x);
        int y1 = max(wid.y, windows[i].y);
        int x2 = min(wid.x + wid.w, windows[i].x + windows[i].w);
        int y2 = min(wid.y + wid.h, windows[i].y + windows[i].h);
        if (x1 < x2 && y1 < y2) return true;
    }
    return false;
}

bool out(window wid)
{
    return wid.x + wid.w > SW || wid.y + wid.h > SH;
}

window getWindow()
{
    return window{rand() % SW, rand() % SH, rand() % SW + 1, rand() % SH + 1};
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    srand(time(NULL));
    cout << SW << ' ' << SH << '\n';
    for (int i = 0; i < 100; i++)
    {
        cout << "OPEN ";
        window wid = getWindow();
        while (overlapped(wid) || out(wid)) wid = getWindow();
        cout << wid.x << ' ' << wid.y << ' ' << wid.w << ' ' << wid.h << '\n';
        windows.push_back(wid);
    }
    for (int i = 1; i <= 128; i++)
    {
        cout << "CLOSE ";
        cout << rand() % SW << ' ' << rand() % SH << '\n';
        cout << "OPEN ";
        cout << rand() % SW << ' ' << rand() % SH << ' ' << rand() % SW + 1 << ' ' << rand() % SH + 1 << '\n';
        cout << "RESIZE ";
        cout << rand() % SW << ' ' << rand() % SH << ' ' << rand() % SW + 1 << ' ' << rand() % SH + 1 << '\n';
        cout << "MOVE ";
        cout << rand() % SW << ' ' << rand() % SH << ' ' << 0 << ' ' << (rand() % 2 ? 1 : -1) * (rand() % SH + 1) << '\n';
        cout << "MOVE ";
        cout << rand() % SW << ' ' << rand() % SH << ' ' << (rand() % 2 ? 1 : -1) * (rand() % SW + 1) << ' ' << 0 << '\n';
    }
    return 0;
}
