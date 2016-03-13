// Trip Routing
// UVa IDs: 186
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

struct segment
{
    int index;
    string startCity, endCity, route;
    int miles;
};

vector < vector < segment > >routes;
vector < string > cityName;
map < string, int >cityIndex;
vector < pair < int, int >>parent;
vector < int >distances;
vector < bool > visited;

void trim(string & line)
{
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (isblank(line[i]))
            line.erase(line.begin() + i);
        else
            break;
    }

    while (line.length())
    {
        if (isblank(line.front()))
            line.erase(line.begin());
        else
            break;
    }
}

void printHeader()
{
    cout << left << setw(20) << "From" << " " << left << setw(20) << "To" <<" ";
    cout << left << setw(10) << "Route" << " " << left << setw(5) << "Miles" << "\n";
    cout << string(20, '-') << " " << string(20, '-') << " ";
    cout << string(10, '-') << " " << string(5, '-') << "\n";
}

int totalMiles = 0;
void findPath(int start, int end)
{
    if (start != parent[end].first)
        findPath(start, parent[end].first);

    cout << left << setw(20)
         << routes[parent[end].first][parent[end].second].startCity
         << " "
         << left << setw(20)
         << routes[parent[end].first][parent[end].second].endCity
         << " "
         << left << setw(10)
         << routes[parent[end].first][parent[end].second].route
         << " "
         << right << setw(5)
         << routes[parent[end].first][parent[end].second].miles
         << "\n";

    totalMiles += routes[parent[end].first][parent[end].second].miles;
}

void printFooter()
{
    cout << string(53, ' ') << string(5, '-') << "\n";
    cout << string(42, ' ') << left << setw(10) << "Total";
    cout << " ";
    cout << right << setw(5) << totalMiles << "\n";
}

void dijkstra(int start)
{
    parent.clear();
    visited.clear();
    distances.clear();

    for (int i = 0; i < routes.size(); i++)
    {
        parent.push_back(make_pair(-1, -1));
        visited.push_back(false);
        distances.push_back(numeric_limits < int >::max());
    }

    distances[start] = 0;
    int minDistance;

    while (visited[start] == false)
    {
        visited[start] = true;
        for (int i = 0; i < routes[start].size(); i++)
        {
            int index = routes[start][i].index;
            if (visited[index] == false)
            {
                if (distances[start] + routes[start][i].miles <
                    distances[index])
                {
                    distances[index] =
                        distances[start] + routes[start][i].miles;
                    parent[index] = make_pair(start, i);
                }
            }
        }

        start = 0;
        minDistance = numeric_limits < int >::max();
        for (int i = 0; i < routes.size(); i++)
            if (visited[i] == false && minDistance > distances[i])
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        trim(line);

        if (line.length() == 0)
            break;

        int miles;
        string startCity, endCity, road;

        int first = 0, second = line.find(',', first);
        startCity = line.substr(first, second);
        first = second + 1, second = line.find(',', first);
        endCity = line.substr(first, second - first);
        first = second + 1, second = line.find(',', first);
        road = line.substr(first, second - first);
        miles = stoi(line.substr(second + 1));

        //cout << startCity << " " << endCity << " " << road << " " << miles << endl;

        if (cityIndex.count(startCity) == 0)
        {
            cityName.push_back(startCity);
            cityIndex[startCity] = cityName.size() - 1;
            vector < segment > segments;
            routes.push_back(segments);
        }

        if (cityIndex.count(endCity) == 0)
        {
            cityName.push_back(endCity);
            cityIndex[endCity] = cityName.size() - 1;
            vector < segment > segments;
            routes.push_back(segments);
        }

        routes[cityIndex[startCity]].push_back((segment)
            {cityIndex[endCity], startCity, endCity, road, miles}
        );
        routes[cityIndex[endCity]].push_back((segment)
            {cityIndex[startCity], endCity, startCity, road, miles}
        );
    }

    while (getline(cin, line))
    {
        trim(line);

        int index = line.find(',');
        int start = cityIndex[line.substr(0, index)];
        int end = cityIndex[line.substr(index + 1)];

        dijkstra(start);

        cout << "\n\n";

        printHeader();
        totalMiles = 0;
        findPath(start, end);
        printFooter();
    }

    return 0;
}
