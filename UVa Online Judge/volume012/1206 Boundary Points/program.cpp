// Boundary Points
// UVa ID: 1206
// Verdict: Accepted
// Submission Date: 2018-04-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
	double x, y;
	
    point (double x = 0, double y = 0): x(x), y(y) {};

	bool operator<(const point &p) const
	{
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}

	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}

	double distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
};

typedef vector<point> polygon;

point pr;

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cw(point a, point b, point c)
{
	return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
	return fabs(cp(a, b, c)) <= EPSILON;
}

bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b)) return pr.distTo(a) <= pr.distTo(b);
    return ccw(pr, a, b);
}

polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());
    if (ch.size() < 3) return ch;

    pr = ch.front();
    sort(ch.begin() + 1, ch.end(), cmpAngle);
	ch.push_back(pr);

	int top = 2, next = 2, total = ch.size() - 1;
	while (next <= total)
	{
	    if (cw(ch[top - 2], ch[top - 1], ch[next])) top--;
	    else 
	    {
	        if (collinear(ch[top - 2], ch[top - 1], ch[next]))
	            ch[top - 1] = ch[next++];
	        else
	            ch[top++] = ch[next++];
        }
	}
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

void skipBlank(string &line, int &idx)
{
    while (idx < line.length() && isblank(line[idx])) idx++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        polygon pg;
        
        string modified;
        for (int i = 0; i < line.length(); i++)
        {
            if (isblank(line[i]) || line[i] == '(') continue;
            modified += line[i];
        }
        
        istringstream iss1(modified);
        string block;
        while (getline(iss1, block, ')'))
        {
            if (block.length() == 0) continue;
            istringstream iss2(block);
            double x, y;
            char comma;
            iss2 >> x >> comma >> y;
            pg.push_back(point(x, y));
        }
        
        polygon ch = grahamConvexHull(pg);
        for (int i = 0; i < ch.size(); i++)
        {
            if (i) cout << ' ';
            cout << '(' << ch[i].x << ',' << ch[i].y << ')';
        }
        cout << '\n';
    }

    return 0;
}
