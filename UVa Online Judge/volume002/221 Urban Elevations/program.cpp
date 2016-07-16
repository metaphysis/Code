// Urban Elevations
// UVa ID: 221
// Verdict: Accepted
// Submission Date: 2016-05-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct building
{
    int index;
    double left, bottom, width, right, depth, height;

    bool operator<(building another) const
    {
        if (left != another.left)
            return left < another.left;
        else
            return bottom < another.bottom;
    }
};

vector < building > buildings;

void findVisibleBuilding()
{
    sort(buildings.begin(), buildings.end());

    cout << buildings.front().index;

    for (int i = 1; i < buildings.size(); i++)
    {
        vector < pair < double, double >>interval;
        interval.push_back(make_pair(buildings[i].left, buildings[i].right));

        for (int j = 0; j < buildings.size(); j++)
        {
            if (buildings[i].index == buildings[j].index)
                continue;

            if (buildings[i].bottom + buildings[i].depth <= buildings[j].bottom)
                continue;

            vector < pair < double, double >>more;
            for (int k = interval.size() - 1; k >= 0; k--)
            {
                if (buildings[i].height <= buildings[j].height)
                {
                    if (interval[k].first >= buildings[j].left &&
                        interval[k].second <= buildings[j].right)
                        interval.erase(interval.begin() + k);

                    if (interval[k].first < buildings[j].left &&
                        interval[k].second > buildings[j].right)
                    {
                        interval.erase(interval.begin() + k);
                        more.push_back(make_pair(interval[k].first,
                                buildings[j].left));
                        more.push_back(make_pair(buildings[j].right,
                                interval[k].second));
                    }
                    else if (interval[k].first < buildings[j].left &&
                        interval[k].second > buildings[j].left &&
                        interval[k].second <= buildings[j].right)
                    {
                        interval.erase(interval.begin() + k);
                        more.push_back(make_pair(interval[k].first,
                                buildings[j].left));
                    }
                    else if (interval[k].first >= buildings[j].left &&
                        interval[k].first < buildings[j].right &&
                        interval[k].second > buildings[j].right)
                    {
                        interval.erase(interval.begin() + k);
                        more.push_back(make_pair(buildings[j].right,
                                interval[k].second));
                    }
                }

            }

            interval.insert(interval.begin(), more.begin(), more.end());

            if (interval.size() == 0)
                break;
        }

        if (interval.size())
            cout << " " << buildings[i].index;
    }

    cout << endl;
}

int main(int argc, char *argv[])
{
    int n, cases = 0, first = true;
    while (cin >> n, n)
    {
        buildings.clear();

        double left, bottom, width, depth, height;
        for (int i = 1; i <= n; i++)
        {
            cin >> left >> bottom >> width >> depth >> height;
            buildings.push_back((building)
                {
                i, left, bottom, width, left + width, depth, height});
        }

        if (first)
            first = false;
        else
            cout << endl;

        cases++;

        cout << "For map #" << cases;
        cout << ", the visible buildings are numbered as follows:" << endl;

        findVisibleBuilding();
    }

    return 0;
}
