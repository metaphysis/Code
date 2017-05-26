// Stars
// UVa ID: 316
// Verdict: Accepted
// Submission Date: 2017-05-27
// UVa Run Time: 0.220s
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

const double EPSILON = 1e-6;

struct star
{
    int x, y, brightness;
};

vector<star> stars1, stars2, constellation1;
map<int, map<int, int>> starsIdx1, starsIdx2;
    
bool cmpXY(int i, int j)
{
    if (stars1[i].x != stars1[j].x) return stars1[i].x < stars1[j].x;
    return stars1[i].y < stars1[j].y;
}

bool cmpBrightness(const star &s1, const star &s2)
{
    if (s1.brightness != s2.brightness) return s1.brightness > s2.brightness;
    if (s1.x != s2.x) return s1.x < s2.x;
    return s1.y < s2.y;
}

int findPolygon(vector<star> &stars, map<int, map<int, int>> &starsIdx, vector<star> &constellation, vector<int> &brightest)
{
    int maxBrightness = 0, times = 0;
    int n = stars.size(), m = constellation.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            
            double theta1 = atan2(stars[j].y - stars[i].y, stars[j].x - stars[i].x);
            double theta2 = atan2(constellation[1].y - constellation[0].y, constellation[1].x - constellation[0].x);
            double rtheta = theta1 - theta2;
            double dist1 = pow(stars[j].x - stars[i].x, 2) + pow(stars[j].y - stars[i].y, 2);
            double dist2 = pow(constellation[1].x - constellation[0].x, 2) + pow(constellation[1].y - constellation[0].y, 2);
            double scaling = sqrt(dist1 / dist2);

            int k = 0, sumOfBrightness = 0;
            vector<int> similar;

            for (k = 0; k < m; k++) 
            {
                double tx = constellation[k].x - constellation[0].x, ty = constellation[k].y - constellation[0].y;

                // rotate
                double rx = tx * cos(rtheta) - ty * sin(rtheta);
                double ry = tx * sin(rtheta) + ty * cos(rtheta);
                
                // scale
                rx *= scaling, ry *= scaling;
                
                // translate
                rx += stars[i].x,  ry += stars[i].y;
                
                // check the coordinate is integer or not
                int ix = (int)floor(rx + EPSILON), iy = (int)floor(ry + EPSILON);
                
                if(fabs(rx - ix) > EPSILON || fabs(ry - iy) > EPSILON) break;
                
                // check the point if exist or not
                if (starsIdx.find(ix) == starsIdx.end()) break;
                if (starsIdx[ix].find(iy) == starsIdx[ix].end()) break;
                
                int idx = starsIdx[ix][iy];
                similar.push_back(idx);
                sumOfBrightness += stars[idx].brightness;
            }

            if (k == m)
            {
                times++;
                if (sumOfBrightness > maxBrightness)
                {
                    maxBrightness = sumOfBrightness;
                    brightest.swap(similar);
                }
            }
        }
        
        return times;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, m, si, x1, y1, brightness;
    string name;

    while (cin >> n, n > 0)
    {
        stars1.clear(), starsIdx1.clear();

        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> brightness;
            stars1.push_back(star{x1, y1, brightness});
            starsIdx1[x1][y1] = i;
        }

        cout << "Map #" << ++cases << '\n';
                    
        cin >> m;
        for (int c = 0; c < m; c++)
        {
            cin >> si >> name;

            constellation1.clear();
            stars2.clear(), starsIdx2.clear();

            for (int i = 0; i < si; i++)
            {
                cin >> x1 >> y1;
                constellation1.push_back(star{x1, y1, 0});
                stars2.push_back(star{x1, y1, 0});
                starsIdx2[x1][y1] = i;
            }

            cout << '\n';

            // special case
            if (si > n)
            {
                cout << name << " occurs 0 time(s) in the map.\n";
                continue;
            }
            
            // special case
            if (si == 1 || si == 2)
            {
                sort(stars1.begin(), stars1.end(), cmpBrightness);

                int times = stars1.size();
                if (si == 2) times = times * (times - 1) / 2;

                cout << name << " occurs " << times << " time(s) in the map.\n";

                if (times > 0)
                {
                    cout << "Brightest occurrence:";
                    for (int i = 0; i < si; i++)
                        cout << " (" << stars1[i].x << ',' << stars1[i].y << ")";
                    cout << '\n';
                }
                
                continue;
            }

            // common case
            vector<int> brightest;
            int times2 = findPolygon(stars2, starsIdx2, constellation1, brightest);
            int times1 = findPolygon(stars1, starsIdx1, constellation1, brightest);

            if (times2 > 0) times1 /= times2;

            sort(brightest.begin(), brightest.end(), cmpXY);
            cout << name << " occurs " << times1 << " time(s) in the map.\n";

            if (times1 > 0)
            {
                cout << "Brightest occurrence:";
                for (auto idx : brightest)
                    cout << " (" << stars1[idx].x << ',' << stars1[idx].y << ")";
                cout << '\n';
            }
        }

        cout << "-----\n";
    }

    return 0;
}
