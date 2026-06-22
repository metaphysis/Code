// Do You Know the Way to San Jose?
// UVa ID: 511
// Verdict: Accepted
// Submission Date: 2017-04-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-7;

struct maps
{
    string name;
    double centerx, centery;
    double leftx, rightx, bottomy, topy;
    double area, ratio;
    double cornerx, cornery;
};

vector<maps> allMaps;
map<string, pair<int, int>> locations;
map<string, vector<pair<int, int>>> cache;
double windowRatio = 0.75;
double currentx, currenty;
string name;
int level, smallest;

double dist(double x1, double y1)
{
    return (currentx - x1) * (currentx - x1) + (currenty - y1) * (currenty - y1);
}

bool cmp(int a, int b)
{
    if (fabs(allMaps[a].area - allMaps[b].area) < epsilon)
    {
        double dist1 = dist(allMaps[a].centerx, allMaps[a].centery);
        double dist2 = dist(allMaps[b].centerx, allMaps[b].centery);
        
        if (fabs(dist1 - dist2) < epsilon)
        {
            double diff1 = fabs(allMaps[a].ratio - windowRatio);
            double diff2 = fabs(allMaps[b].ratio - windowRatio);

            if (fabs(diff1 - diff2) < epsilon)
            {
                dist1 = dist(allMaps[a].cornerx, allMaps[a].cornery);
                dist2 = dist(allMaps[b].cornerx, allMaps[b].cornery);
                
                if (fabs(dist1 - dist2) < epsilon)
                    return allMaps[a].leftx < allMaps[b].leftx;
                else
                    return dist1 < dist2;
            }
            else
                return diff1 < diff2;
        }
        else
            return dist1 < dist2;
    }
    else
        return allMaps[a].area > allMaps[b].area;
}

bool readMap()
{
    double x1, y1, x2, y2;
    
    cin >> name;
    if (name == "LOCATIONS") return false;
    cin >> x1 >> y1 >> x2 >> y2;
    
    maps m;
    m.name = name;
    m.centerx = (x1 + x2) / 2.0, m.centery = (y1 + y2) / 2.0;
    m.leftx = min(x1, x2), m.rightx = max(x1, x2);
    m.bottomy = min(y1, y2), m.topy = max(y1, y2);
    m.area = fabs((m.rightx - m.leftx) * (m.topy - m.bottomy));
    m.ratio = fabs((m.topy - m.bottomy) / (m.rightx - m.leftx));
    m.cornerx = m.rightx, m.cornery = m.bottomy;
    allMaps.push_back(m);

    return true;
}

bool inMap(double x1, double y1, maps &m)
{
    return x1 >= m.leftx && x1 <= m.rightx && y1 >= m.bottomy && y1 <= m.topy;
}

bool readLocation()
{
    double x1, y1;
    
    cin >> name;
    if (name == "REQUESTS") return false;
    cin >> x1 >> y1;
    
    locations.insert(make_pair(name, make_pair(0, 0)));
    vector<int> candidate;
    for (int i = 0; i < allMaps.size(); i++)
        if (inMap(x1, y1, allMaps[i]))
            candidate.push_back(i);
    
    currentx = x1, currenty = y1;
    sort(candidate.begin(), candidate.end(), cmp);
    
    vector<pair<int, int>> info;
    if (candidate.size() > 0)
    {
        double area = allMaps[candidate.front()].area;
        level = 1, smallest = candidate.front();
        for (int i = 0; i < candidate.size(); i++)
        {
            if (fabs(allMaps[candidate[i]].area - area) < epsilon)
                info.push_back(make_pair(level, candidate[i]));
            else
            {
                level += 1;
                area = allMaps[candidate[i]].area;
                info.push_back(make_pair(level, candidate[i]));
                smallest = candidate[i];
            }
        }
        locations[name].first = level, locations[name].second = smallest;
    }
    cache[name] = info;
    
    return true;
}

bool readRequest()
{
    cin >> name;
    if (name == "END") return false;

    cin >> level;

    cout << name << " at detail level " << level;
    if (locations.find(name) == locations.end())
        cout << " unknown location\n";
    else
    {
        if (cache[name].size() == 0)
            cout << " no map contains that location\n";
        else
        {
            if (level <= locations[name].first)
            {
                for (auto pair : cache[name])
                    if (pair.first == level)
                    {
                        cout << " using " << allMaps[pair.second].name << '\n';
                        break;
                    }
            } 
            else
            {
                cout << " no map at that detail level; using ";
                cout << allMaps[locations[name].second].name << '\n';
            }
        }
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> name;

    while (readMap()) {}
    while (readLocation()) {}
    while (readRequest()) {}

    return 0;
}
