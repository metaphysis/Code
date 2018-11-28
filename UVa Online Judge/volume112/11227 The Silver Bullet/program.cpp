// The Silver Bullet
// UVa ID: 11227
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};
point ps[110];

int getInt(string x)
{
    int sign = 1;
    if (x.front() == '-')
    {
        sign = -1;
        x.erase(x.begin());
    }
    int n = 0;
    for (auto c : x)
        if (isdigit(c))
            n = n * 10 + c - '0';
    return n * sign;
}

int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool collinear(point a, point b, point c)
{
    return cp(a, b, c) == 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string x, y;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        int total = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            point p = point(getInt(x), getInt(y));
            bool exist = false;
            for (int j = 0; j < total; j++)
                if (p.x == ps[j].x && p.y == ps[j].y)
                {
                    exist = true;
                    break;
                }
            if (!exist) ps[total++] = p;
        }
        cout << "Data set #" << cs;
        if (total == 1)
        {
            cout << " contains a single gnu.\n";
        }
        else if (total == 2)
        {
            cout << " contains 2 gnus, out of which a maximum of 2 are aligned.\n";
        }
        else
        {
            int most = 0;
            sort(ps, ps + total);
            for (int i = 0; i < total; i++)
                for (int j = i + 1; j < total; j++)
                {
                    int cnt = 2;
                    for (int k = j + 1; k < total; k++)
                        if (collinear(ps[i], ps[j], ps[k]))
                            cnt++;
                    most = max(most, cnt);
                }
            cout << " contains " << total << " gnus, out of which a maximum of ";
            cout << most << " are aligned.\n";
        }
    }

    return 0;
}
