// Murcia's Skyline
// UVa ID: 11790
// Verdict: Accepted
// Submission Date: 2017-11-04
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct building { int height, width; };

int lis(vector<building> buildings)
{
    vector<int> widths(buildings.size(), 0);
    for (int i = 0; i < buildings.size(); i++)
        widths[i] = buildings[i].width;

    for (int i = 0; i < buildings.size(); i++)
        for (int j = 0; j < i; j++)
            if (buildings[i].height > buildings[j].height && widths[i] < widths[j] + buildings[i].width)
                widths[i] = widths[j] + buildings[i].width;
                
    return *max_element(widths.begin(), widths.end());
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, height, width;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        vector<building> buildings;
        vector<int> heights, widths;
        
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> height;
            heights.push_back(height);
        }
        for (int i = 0; i < n; i++)
        {
            cin >> width;
            widths.push_back(width);
        }
        for (int i = 0; i < n; i++)
            buildings.push_back(building{heights[i], widths[i]});
            
        int increasing = lis(buildings);
        reverse(buildings.begin(), buildings.end());
        int decreasing = lis(buildings);
        
        cout << "Case " << c << ". ";
        if (increasing >= decreasing)
        {
            cout << "Increasing (" << increasing << "). Decreasing (" << decreasing << ").\n";
        }
        else
        {
            cout << "Decreasing (" << decreasing << "). Increasing (" << increasing << ").\n";
        }
    }

    return 0;
}
