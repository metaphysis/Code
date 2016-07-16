// Lining Up
// UVa ID: 270
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.410s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct point
{
    int x, y;
};

bool cmp(point a, point b)
{
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

vector < point > points;
int paired[701][701], counter[701];

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

int getMaxPoints()
{
    sort(points.begin(), points.end(), cmp);
    
    
    for (int i = 0; i < points.size(); i++)
        for (int j = 0; j < points.size(); j++)
            paired[i][j] = 0;
    
    int maxPoint = 0;   
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
            if (paired[i][j] == 0)
            {
                paired[i][j] = 1;

                int index = 2;
                counter[0] = i;
                counter[1] = j;
                
                for (int k = j + 1; k < points.size(); k++)
                {
                    if (crossProduct(points[i], points[j], points[k]) == 0)
                        counter[index++] = k;
                }
                
                maxPoint = max(maxPoint, index);
            }
    }
    
    return maxPoint;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    bool first = true;
    
    int cases;
    string input;
    
    getline(cin, input);
    cases = stoi(input);
    getline(cin, input);
    
    while (cases--)
    {
        points.clear();
        while (getline(cin, input))
        {
            if (input.length() == 0)
                break;
                
            int x, y;
            istringstream iss(input);
            iss >> x >> y;
            points.push_back((point){x, y});
        }
        
        if (first)
            first = false;
        else
            cout << "\n";
            
        cout << getMaxPoints() << "\n";
    }
    
    
	return 0;
}
