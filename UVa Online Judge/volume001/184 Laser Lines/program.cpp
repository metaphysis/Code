// Laser Lines
// UVa ID: 184
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 1.176s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};

struct line
{
    point start, end;
};

vector<vector<point>> lines;
vector<point> points;

bool pointCmp(point a, point b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool vectorCmp(vector < point > a, vector < point > b)
{
    int index = 0;
    while (index < a.size() && index < b.size())
    {
        if (a[index].x == b[index].x && a[index].y == b[index].y)
            index++;
        else
            return pointCmp(a[index], b[index]);
    }

    if (index < a.size())
        return false;
    else
        return true;
}

void print()
{
    if (lines.size() == 0)
    {
        cout << "No lines were found\n";
        return;
    }

    for (int i = 0; i < lines.size(); i++)
        sort(lines[i].begin(), lines[i].end(), pointCmp);
    sort(lines.begin(), lines.end(), vectorCmp);

    cout << "The following lines were found:\n";
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
            cout << "(" << right << setw(4) << lines[i][j].x << ","
                 << right << setw(4) << lines[i][j].y << ")";
        cout << "\n";
    }
}

bool isOnLine(point a, point b, point c)
{
    return ((c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y)) == 0;
}

void find()
{
    sort(points.begin(), points.end(), pointCmp);

    vector<line> slopes;
    for (int i = 0; i < points.size() - 1; i++)
        for (int j = i + 1; j < points.size(); j++)
        {
            bool existed = false;
            for (int k = 0; k < slopes.size(); k++)
            {
                if (isOnLine(slopes[k].start, slopes[k].end, points[i]) &&
                        isOnLine(slopes[k].start, slopes[k].end, points[j]))
                {
                    existed = true;
                    break;
                }
            }

            if (existed == false)
                slopes.push_back((line){points[i], points[j]});
        }

    lines.clear();
    for (int i = 0; i < slopes.size(); i++)
    {
        vector < point > online;
        for (int j = 0; j < points.size(); j++)
            if (isOnLine(slopes[i].start, slopes[i].end, points[j]))
                online.push_back(points[j]);

        lines.push_back(online);
    }

    for (int i = lines.size() - 1; i >= 0; i--)
        if (lines[i].size() == 2)
            lines.erase(lines.begin() + i);

    print();
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    int x, y;
    while (cin >> x >> y)
    {
        if (x == 0 && y == 0)
            break;
        else
            points.push_back((point){x, y});

        while (cin >> x >> y)
        {
            if (x == 0 && y == 0)
            {
                find();
                points.clear();
                break;
            }
            else
                points.push_back((point){x, y});
        }
    }

    return 0;
}
