// Window Manager
// UVa ID: 1721
// Verdict: Accepted
// Submission Date: 2021-12-23
// UVa Run Time: 1.250s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

struct window { int x, y, w, h; };

int SW, SH, added[320];

vector<window> windows;
vector<string> cmds;

bool overlapped(int wid, int x, int y, int w, int h)
{
    for (int i = 0; i < windows.size(); i++)
    {
        if (i == wid) continue;
        int x1 = max(x, windows[i].x);
        int y1 = max(y, windows[i].y);
        int x2 = min(x + w, windows[i].x + windows[i].w);
        int y2 = min(y + h, windows[i].y + windows[i].h);
        if (x1 < x2 && y1 < y2) return true;
    }
    return false;
}

bool out(int x, int y, int w, int h)
{
    return x + w > SW || y + h > SH;
}

int getId(int x, int y)
{
    for (int i = 0; i < windows.size(); i++)
        if (windows[i].x <= x && x < windows[i].x + windows[i].w && windows[i].y <= y && y < windows[i].y + windows[i].h)
            return i;
    return -1;
}

pair<int, vector<int>> getNextWindow(int wid, int dx, int dy)
{
    int nearest = -1;
    vector<int> nid;
    if (dx > 0)
    {
        if (windows[wid].x + windows[wid].w == SW) return make_pair(nearest, nid);
        nearest = SW - (windows[wid].x + windows[wid].w);
        for (int i = 0; i < windows.size(); i++)
        {
            if (added[i]) continue;
            if (windows[i].y + windows[i].h <= windows[wid].y || windows[i].y >= windows[wid].y + windows[wid].h) continue;
            if (windows[i].x < windows[wid].x + windows[wid].w) continue;
            int d = windows[i].x - (windows[wid].x + windows[wid].w);
            assert(d >= 0);
            if (d < nearest)
            {
                nearest = d;
                nid.clear();
                nid.push_back(i);
            }
            else if (d == nearest)
            {
                nid.push_back(i);
            }
        }
    }
    
    if (dx < 0)
    {
        if (!windows[wid].x) return make_pair(nearest, nid);
        nearest = windows[wid].x;
        for (int i = 0; i < windows.size(); i++)
        {
            if (added[i]) continue;
            if (windows[i].y + windows[i].h <= windows[wid].y || windows[i].y >= windows[wid].y + windows[wid].h) continue;
            if (windows[i].x + windows[i].w > windows[wid].x) continue;
            int d = windows[wid].x - (windows[i].x + windows[i].w);
            assert(d >= 0);
            if (d < nearest)
            {
                nearest = d;
                nid.clear();
                nid.push_back(i);
            }
            else if (d == nearest)
            {
                nid.push_back(i);
            }
        }
    }
    
    if (dy > 0)
    {
        if (windows[wid].y + windows[wid].h == SH) return make_pair(nearest, nid);
        nearest = SH - (windows[wid].y + windows[wid].h);
        if (nearest < 0)
        {
            cout << wid << ' ' << windows[wid].y << ' ' << windows[wid].h << ' ' << SH << endl;
            assert(false);
        }
        for (int i = 0; i < windows.size(); i++)
        {
            if (added[i]) continue;
            if (windows[i].x + windows[i].w <= windows[wid].x || windows[i].x >= windows[wid].x + windows[wid].w) continue;
            if (windows[i].y < windows[wid].y + windows[wid].h) continue;
            int d = windows[i].y - (windows[wid].y + windows[wid].h);
            assert(d >= 0);
            if (d < nearest)
            {
                nearest = d;
                nid.clear();
                nid.push_back(i);
            }
            else if (d == nearest)
            {
                nid.push_back(i);
            }
        }
    }
    
    if (dy < 0)
    {
        if (!windows[wid].y) return make_pair(nearest, nid);
        nearest = windows[wid].y;
        for (int i = 0; i < windows.size(); i++)
        {
            if (added[i]) continue;
            if (windows[i].x + windows[i].w <= windows[wid].x || windows[i].x >= windows[wid].x + windows[wid].w) continue;
            if (windows[i].y + windows[i].h > windows[wid].y) continue;
            int d = windows[wid].y - (windows[i].y + windows[i].h);
            assert(d >= 0);
            if (d < nearest)
            {
                nearest = d;
                nid.clear();
                nid.push_back(i);
            }
            else if (d == nearest)
            {
                nid.push_back(i);
            }
        }
    }
    return make_pair(nearest, nid);
}

void move(int cid, int wid, int x, int y, int dx, int dy)
{
    memset(added, 0, sizeof added);
    vector<int> sweep;
    sweep.push_back(wid);
    added[wid] = 1;
    int shifted = 0;
    while (true)
    {
        int delta = INF;
        vector<int> nid;
        for (int i = 0; i < sweep.size() && delta; i++)
        {
            pair<int, vector<int>> r = getNextWindow(sweep[i], dx, dy);
            if (r.first < delta)
            {
                delta = r.first;
                nid = r.second;
            }
            else if (r.first == delta)
            {
                nid.insert(nid.end(), r.second.begin(), r.second.end());
            }
            if (delta == -1) break;
        }
        if (delta == -1) break;
        delta = min(delta, abs(dx + dy) - shifted);
        for (int i = 0; i < sweep.size(); i++)
        {
            if (dx)
                windows[sweep[i]].x += delta * (dx > 0 ? 1 : -1);
            else
                windows[sweep[i]].y += delta * (dy > 0 ? 1 : -1);
        }
        for (auto id : nid)
        {
            if (added[id]) continue;
            sweep.push_back(id);
            added[id] = 1;
        }
        shifted += delta;
        if (shifted >= abs(dx + dy)) break;
    }
    if (shifted < abs(dx + dy))
    {
        cout << "Command " << cid << ": MOVE - moved ";
        cout << shifted << " instead of " << abs(dx + dy) << '\n';
    }
}

void process()
{
    if (!cmds.size()) return;
    windows.clear();
    istringstream iss;
    iss.str(cmds[0]);
    iss >> SW >> SH;
    string cmd;
    int x, y, w, h;
    for (int i = 1; i < cmds.size(); i++)
    {
        iss.clear();
        iss.str(cmds[i]);
        iss >> cmd;
        if (cmd == "OPEN")
        {
            iss >> x >> y >> w >> h;
            if (overlapped(-1, x, y, w, h) || out(x, y, w, h))
                cout << "Command " << i << ": OPEN - window does not fit" << '\n'; 
            else
                windows.push_back(window{x, y, w, h});
        }
        else if (cmd == "CLOSE")
        {
            iss >> x >> y;
            int wid = getId(x, y);
            if (wid == -1) cout << "Command " << i << ": CLOSE - no window at given position" << '\n';
            else windows.erase(windows.begin() + wid);
        }
        else if (cmd == "RESIZE")
        {
            iss >> x >> y >> w >> h;
            int wid = getId(x, y);
            if (wid == -1) cout << "Command " << i << ": RESIZE - no window at given position" << '\n';
            else
            {
                if (overlapped(wid, windows[wid].x, windows[wid].y, w, h) || out(windows[wid].x, windows[wid].y, w, h))
                    cout << "Command " << i << ": RESIZE - window does not fit" << '\n';
                else
                    windows[wid].w = w, windows[wid].h = h;
            }
        }
        else
        {
            iss >> x >> y >> w >> h;
            int wid = getId(x, y);
            if (wid == -1) cout << "Command " << i << ": MOVE - no window at given position" << '\n';
            else move(i, wid, x, y, w, h);
        }
    }
    cout << windows.size() << " window(s):\n";
    for (int i = 0; i < windows.size(); i++)
    {
        cout << windows[i].x << ' ' << windows[i].y;
        cout << ' ';
        cout << windows[i].w << ' ' << windows[i].h;
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{   
    string line;
    while (getline(cin, line))
    {
        if (!line.length()) break;
        if (isdigit(line.front()))
        {
            process();
            cmds.clear();
        }
        cmds.push_back(line);
    }
    process();
    return 0;
}
