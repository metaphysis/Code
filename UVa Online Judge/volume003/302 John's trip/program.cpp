// John's trip
// UVa ID: 302
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct edge
{
    int to, street;
    bool operator<(const edge & another) const
    {
        return street < another.street;
    }
};

int x, y, z, start;
map<int, multiset<edge>> adjacentEdges;
vector<bool> traveled(2000);
vector<int> trip;

void euler(int vertex)
{
    for (auto e : adjacentEdges[vertex])
        if (!traveled[e.street])
        {
            traveled[e.street] = true;
            euler(e.to);
            trip.insert(trip.begin(), e.street);
        }
}

void findEulerCircuit()
{
    for (auto element : adjacentEdges)
        if (element.second.size() % 2 == 1)
        {
            cout << "Round trip does not exist." << endl << endl;
            return;
        }

    fill(traveled.begin(), traveled.end(), false);
    trip.clear();

    euler(start);

    for (int i = 0; i < trip.size(); i++)
        if (i > 0)
            cout << " " << trip[i];
        else
            cout << trip[i];
    cout << endl << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int dataItems = 0;
    while (cin >> x >> y)
    {
        if (x == 0 && y == 0)
        {
            if (dataItems == 0)
                break;

            findEulerCircuit();

            adjacentEdges.clear();
            dataItems = 0;
            continue;
        }

        cin >> z;
        
        adjacentEdges[x].insert((edge){y, z});
        adjacentEdges[y].insert((edge){x, z});

        if (++dataItems == 1)
            start = min(x, y);
    }

    return 0;
}
