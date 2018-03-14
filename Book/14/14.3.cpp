#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100000, INF = 0x3fffffff;
const int BOTTOM = 0, LEFT = 1, RIGHT = 2, TOP = 3;

struct point {
    int x, y;
    point(int x = 0, int y = 0): x(x), y(y) {}
};

struct segment {
    point p1, p2;
    segment(point p1, point p2): p1(p1), p2(p2) {}
};

struct EndPoint {
    point p;
    int epIdx, epCode;
    EndPoint() {}
    EndPoint(point p, int epIdx, int epCode): p(p), epIdx(epIdx), epCode(epCode) {}
    bool operator<(const EndPoint &ep) const
    {
        if (p.y == ep.p.y) return epCode < ep.epCode;
        return p.y < ep.p.y;
    }
};

EndPoint EP[2 * MAXV];

int manhattanIntersection(vector<segment> S)
{
    int n = S.size();

    for (int i = 0, k = 0; i < n; i++)
    {
        if (S[i].p1.y == S[i].p2.y)
        {
            if (S[i].p1.x > S[i].p2.x) swap(S[i].p1, S[i].p2);
        }
        else
        {
            if (S[i].p1.y > S[i].p2.y) swap(S[i].p1, S[i].p2);
        }
        
        if (S[i].p1.y == S[i].p2.y)
        {
            EP[k++] = EndPoint(S[i].p1, i, LEFT);
            EP[k++] = EndPoint(S[i].p2, i, RIGHT);
        }
        else
        {
            EP[k++] = EndPoint(S[i].p1, i, BOTTOM);
            EP[k++] = EndPoint(S[i].p2, i, TOP);
        }
    }

    sort(EP, EP + (2 * n));

    set<int> BT; BT.insert(INF);
    int cnt = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        if (EP[i].epCode == TOP)
        {
            BT.erase(EP[i].p.x);
        }
        else if (EP[i].epCode == BOTTOM)
        {
            BT.insert(EP[i].p.x);
        }
        else if (EP[i].epCode == LEFT)
        {
            auto begin = BT.lower_bound(S[EP[i].epIdx].p1.x);
            auto end = BT.upper_bound(S[EP[i].epIdx].p2.x);
            cnt += distance(begin, end);
        }
    }

    return cnt;
}

int main(int argc, char *argv[])
{
    return 0;
}
