// Of Circles and Squares
// UVa ID: 10823
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct object
{
    int type, px, py, length, r, g, b;
} objects[110];

bool isOnSquare(object &o, int x, int y)
{
    if (x == o.px && y >= o.py && y <= o.py + o.length) return true;
    if (y == o.py && x >= o.px && x <= o.px + o.length) return true;
    if (x == o.px + o.length && y >= o.py && y <= o.py + o.length) return true;
    if (y == o.py + o.length && x >= o.px && x <= o.px + o.length) return true;
    return false;
}

bool isInSquare(object &o, int x, int y)
{
    return x > o.px && x < o.px + o.length && y > o.py && y < o.py + o.length;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, R, P;
    string object_type;

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> R >> P;
        for (int i = 0; i < R; i++)
        {
            cin >> object_type;
            cin >> objects[i].px >> objects[i].py >> objects[i].length >> objects[i].r >> objects[i].g >> objects[i].b;
            objects[i].type = (object_type == "SQUARE");
        }
        if (cs > 1) cout << '\n';
        cout << "Case " << cs << ":\n";
        for (int i = 0, x, y; i < P; i++)
        {
            cin >> x >> y;
            int r = 0, g = 0, b = 0;
            int cnt = 0;
            bool on_borderline = false;
            for (int j = 0; j < R; j++)
            {
                // Circle.
                if (objects[j].type == 0)
                {
                    // Is on borderline?
                    int t1 = (x - objects[j].px) * (x - objects[j].px) + (y - objects[j].py) * (y - objects[j].py);
                    int t2 = objects[j].length * objects[j].length;
                    if (t1 == t2)
                    {
                        on_borderline = true;
                        break;
                    }
                    // Is in?
                    if (t1 < t2)
                    {
                        cnt++;
                        r += objects[j].r, g += objects[j].g, b += objects[j].b;
                    }
                }
                // Square.
                else
                {
                    // Is on borderline?
                    if (isOnSquare(objects[j], x, y))
                    {
                        on_borderline = true;
                        break;
                    }
                    // Is in?
                    if (isInSquare(objects[j], x, y))
                    {
                        cnt++;
                        r += objects[j].r, g += objects[j].g, b += objects[j].b;
                    }
                }
            }
            if (cnt)
            {
                cnt *= 10;
                r = (r * 10 + cnt / 2) / cnt;
                g = (g * 10 + cnt / 2) / cnt;
                b = (b * 10 + cnt / 2) / cnt;
            }
            if (cnt == 0) r = g = b = 255;
            if (on_borderline) r = g = b = 0;
            cout << "(" << r << ", " << g << ", " << b << ")\n";
        }
    }

    return 0;
}
