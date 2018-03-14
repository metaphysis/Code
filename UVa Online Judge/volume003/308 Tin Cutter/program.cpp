// Tin Cutter
// UVa ID: 308
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};

struct segment
{
    point start, end;
    
    bool operator==(const segment &s) const
    {
        return start.x == s.start.x && start.y == s.start.y && end.x == s.end.x && end.y == s.end.y;
    }
    
    bool operator<(const segment &s) const
    {
        if (start.y == end.y)
            return start.y < s.start.y;
        else
            return start.x < s.start.x;
    }
};

struct rectangle
{
    point vertex[4];
};

vector<vector<int>> edges;
vector<int> visited(1000);
vector<segment> horizontal, vertical;
vector<rectangle> rectangles;

bool intersect(segment i, segment j)
{
    return j.start.x >= i.start.x && j.start.x <= i.end.x && i.start.y >= j.start.y && i.start.y <= j.end.y;
}

bool getRectangle(int i, int j, int k, int l)
{
    if (!intersect(horizontal[i], vertical[k])) return false;
    if (!intersect(horizontal[i], vertical[l])) return false;
    if (!intersect(horizontal[j], vertical[k])) return false;
    if (!intersect(horizontal[j], vertical[l])) return false;

    rectangle rect;
    rect.vertex[0] = (point){vertical[k].start.x, horizontal[i].start.y};
    rect.vertex[1] = (point){vertical[k].start.x, horizontal[j].start.y};
    rect.vertex[2] = (point){vertical[l].start.x, horizontal[j].start.y};
    rect.vertex[3] = (point){vertical[l].start.x, horizontal[i].start.y};
    rectangles.push_back(rect);
}

bool pointInRect(point v, int i)
{
    return v.x > rectangles[i].vertex[0].x && v.x < rectangles[i].vertex[2].x &&
        v.y > rectangles[i].vertex[0].y && v.y < rectangles[i].vertex[2].y;
}

bool pointOnRect(point v, int i)
{
    return v.x >= rectangles[i].vertex[0].x && v.x <= rectangles[i].vertex[2].x &&
        v.y >= rectangles[i].vertex[0].y && v.y <= rectangles[i].vertex[2].y;    
}

bool overlapped(int i, int j)
{
    int on_edge = 0;
    for (int v = 0; v < 4; v++)
    {
        if (pointInRect(rectangles[i].vertex[v], j))
            return true;
        if (pointOnRect(rectangles[i].vertex[v], j))
            on_edge++;
    }

    return on_edge >= 2;
}

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        ++cases;
        horizontal.clear(); vertical.clear();
        for (int i = 1; i <= n; i++)
        {
            segment s;
            cin >> s.start.x >> s.start.y >> s.end.x >> s.end.y;
            //if (cases == 67)
                //cout << s.start.x << ' ' << s.start.y << ' ' << s.end.x << ' ' << s.end.y << '\n';
                
            if (s.start.y == s.end.y)
            {
                if (s.start.x > s.end.x) swap(s.start.x, s.end.x);
                horizontal.push_back(s);
            }
            else
            {
                if (s.start.y > s.end.y) swap(s.start.y, s.end.y);
                vertical.push_back(s);
            }
        }

        //continue;
        
        sort(horizontal.begin(), horizontal.end());
        horizontal.erase(unique(horizontal.begin(), horizontal.end()), horizontal.end());
        
        sort(vertical.begin(), vertical.end());
        vertical.erase(unique(vertical.begin(), vertical.end()), vertical.end());

        rectangles.clear();
        int nhorizontal = horizontal.size(), nvertical = vertical.size();
        for (int i = 0; i < nhorizontal; i++)
            for (int j = i + 1; j < nhorizontal; j++)
            {
                if (horizontal[i].start.y == horizontal[j].start.y) continue;
                
                for (int k = 0; k < nvertical; k++)
                    for (int l = k + 1; l < nvertical; l++)
                    {
                        if (vertical[k].start.x == vertical[l].start.x) continue;
                        
                        getRectangle(i, j, k, l);
                    }
            }

        int nrect = rectangles.size();
        edges.assign(nrect, vector<int>());
        
        for (int i = 0; i < nrect; i++)
            for (int j = i + 1; j < nrect; j++)
                if (overlapped(i, j) || overlapped(j, i))
                {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
                
        int holes = 0;
        fill(visited.begin(), visited.end(), 0);
        for (int i = 0; i < nrect; i++)
            if (!visited[i])
            {
                holes++;
                dfs(i);
            }
            
        cout << holes << '\n';
    }
    
	return 0;
}
