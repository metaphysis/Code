// Stars
// UVa ID: 316
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct point
{
    int x, y;

    point (int x = 0, int y = 0) : x(x) , y(y) {}

    point operator - (point p) { return point(x - p.x, y - p.y); }
};

struct star
{
    point p;
    int brightness;
};

int cases = 0;
int n, m, si, x, y, brightness;
long long int d1[1024][1024], d2[64][64];
string name;
vector<star> stars, backup;
vector<point> constellation;
int times = 0, maxBrightness = 0;
vector<int> brightest;

bool cmpXY(int i, int j)
{
    if (stars[i].p.x != stars[j].p.x) return stars[i].p.x < stars[j].p.x;
    else return stars[i].p.y < stars[j].p.y;
}

bool cmpBrightness(const star &s1, const star &s2)
{
    if (s1.brightness != s2.brightness) return s1.brightness > s2.brightness;
    else if (s1.p.x != s2.p.x) return s1.p.x < s2.p.x;
    else return s1.p.y < s2.p.y;
}

void findPoint()
{
    sort(stars.begin(), stars.end(), cmpBrightness);

    cout << name << " occurs " << n << " time(s) in the map.\n";
    cout << "Brightest occurrence:";
    cout << " (" << stars[0].p.x << ',' << stars[0].p.y << ")\n";
}

void findLine()
{
    sort(stars.begin(), stars.end(), cmpBrightness);

    times = n * (n - 1) / 2;
    cout << name << " occurs " << times << " time(s) in the map.\n";

    if (times > 0)
    {
        cout << "Brightest occurrence:";
        cout << " (" << stars[0].p.x << ',' << stars[0].p.y << ")";
        cout << " (" << stars[1].p.x << ',' << stars[1].p.y << ")\n";
    }
}

long long int getDist(point &p1, point &p2)
{
    int offsetx = p1.x - p2.x, offsety = p1.y - p2.y;
    return offsetx * offsetx + offsety * offsety;
}

long long int norm(point &p0)
{
    return p0.x * p0.x + p0.y * p0.y;
}

long long int dotProduct(point &p0, point &p1)
{
    return p0.x * p1.x + p0.y * p1.y;
}

long long int crossProduct(point &p0, point &p1, point &p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool isSameAngle(point &pi, point &pj, point &pk, point &pii, point &pjj, point &pkk)
{
    point v1, v2, v3, v4;

    v1 = pk - pj, v2 = pj - pi, v3 = pkk - pjj, v4 = pii - pjj;

    long long int dp1 = dotProduct(v1, v2);
    long long int dp2 = dotProduct(v3, v4);
    long long int cosa1 = dp1 * dp1 * norm(v3) * norm(v4);
    long long int cosa2 = dp2 * dp2 * norm(v1) * norm(v2);
    if (cosa1 != cosa2) return false;

    long long int cp1 = crossProduct(pi, pj, pk);
    long long int cp2 = crossProduct(pii, pjj, pkk);
    if (cp1 * cp2 < 0) return false;

    return true;
}

bool similarToEnd(int i, int j, vector<int> &selected)
{
    int used[1024] = {0};

    selected.push_back(i), selected.push_back(j);
    used[i] = used[j] = 1;

    int idx = 0, size = constellation.size() - 2;
    while (idx < size)
    {
        int updated = 0;
        for (int k = 0; k < stars.size(); k++)
        {
            if (used[k]) continue;

            // 相邻顶点间的距离等比例。
            if (d1[j][k] * d2[idx][idx + 1] != d2[idx + 1][idx + 2] * d1[i][j]) continue;

            // 多边形邻边的夹角相等。
            if (!isSameAngle(stars[i].p, stars[j].p, stars[k].p, constellation[idx], constellation[idx + 1], constellation[idx + 2])) continue;

            selected.push_back(k);
            updated = 1, used[k] = 1, i = j, j = k;
            break;
        }

        if (!updated) break;

        idx++;
    }

    return idx >= size;
}

void findPolygon()
{
    for (int i = 0; i < constellation.size(); i++)
        for (int j = i + 1; j < constellation.size(); j++)
            d2[i][j] = d2[j][i] = getDist(constellation[i], constellation[j]);

    times = 0, maxBrightness = 0, brightest.clear();

    for (int i = 0; i < stars.size(); i++)
        for (int j = 0; j < stars.size(); j++)
        {
            if (d1[i][j] == 0) continue;
            //if ((d1[i][j] % d2[0][1]) != 0 && (d2[0][1] % d1[i][j]) != 0) continue;

            vector<int> selected;
            if (similarToEnd(i, j, selected))
            {
                times++;
                int sumOfBrightness = 0;
                for (auto starIdx : selected) sumOfBrightness += stars[starIdx].brightness;
                if (sumOfBrightness > maxBrightness)
                {
                    maxBrightness = sumOfBrightness;
                    brightest.swap(selected);
                }
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        stars.clear(), backup.clear();

        for (int i = 0; i < n; i++)
        {
            cin >> x >> y >> brightness;
            stars.push_back(star{point{x, y}, brightness});
        }

        for (int i = 0; i < stars.size(); i++)
            for (int j = i; j < stars.size(); j++)
                d1[i][j] = d1[j][i] = getDist(stars[i].p, stars[j].p);

        cout << "Map #" << ++cases << '\n';

        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> si >> name;

            constellation.clear();
            for (int j = 0; j < si; j++)
            {
                cin >> x >> y;
                constellation.push_back(point{x, y});
                backup.push_back(star{point{x, y}, 0});
            }

            cout << '\n';

            if (si == 1) { findPoint(); continue; }
            if (si == 2) { findLine(); continue; }
            if (si > n) { cout << name << " occurs 0 time(s) in the map.\n"; continue; }

            backup.swap(stars);

            for (int i = 0; i < stars.size(); i++)
                for (int j = i; j < stars.size(); j++)
                    d1[i][j] = d1[j][i] = getDist(stars[i].p, stars[j].p);
  
            findPolygon();

            int degreeOfDuplication = times;

            stars.swap(backup);

            for (int i = 0; i < backup.size(); i++)
                for (int j = i; j < backup.size(); j++)
                    d1[i][j] = d1[j][i] = getDist(stars[i].p, stars[j].p);

            findPolygon();

            times /= degreeOfDuplication;

            sort(brightest.begin(), brightest.end(), cmpXY);
            cout << name << " occurs " << times << " time(s) in the map.\n";
            if (times > 0)
            {
                cout << "Brightest occurrence:";
                for (auto starIdx : brightest)
                    cout << " (" << stars[starIdx].p.x << ',' << stars[starIdx].p.y << ")";
                cout << '\n';
            }
        }

        cout << "-----\n";
    }

    return 0;
}
