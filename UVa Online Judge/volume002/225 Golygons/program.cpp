// Golygons
// UVa ID: 225 
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.390s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};

vector<point> blocks;
vector<int> golygons(30);

string headingText = "ensw";
int turn[4][2] = { {1, 2}, {0, 3}, {0, 3}, {1, 2} };
int direction[4][2] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };
int grid[500][500] = { 0 }, base = 250;
int numberOfGolygons, longestEdge;

bool blocked(point start, point end)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].x == start.x && blocks[i].x == end.x)
            if (blocks[i].y >= min(start.y, end.y)
                    && blocks[i].y <= max(start.y, end.y))
                return true;
        if (blocks[i].y == start.y && blocks[i].y == end.y)
            if (blocks[i].x >= min(start.x, end.x)
                    && blocks[i].x <= max(start.x, end.x))
                return true;
    }

    return false;
}

void dfs(point traveler, int heading, int edge)
{
    if ((abs(traveler.x) + abs(traveler.y)) > ((edge + longestEdge) * (longestEdge - edge + 1) / 2))
	    return;
		    
    if (heading < 0)
    {
        for (int i = 0; i < 4; i++)
        {
            point newTraveler;
            newTraveler.x = traveler.x + direction[i][0];
            newTraveler.y = traveler.y + direction[i][1];
            
            if (blocked(traveler, newTraveler))
                continue;
                
            grid[newTraveler.x + base][newTraveler.y + base] = 1;
            golygons[edge] = i;
            dfs(newTraveler, i, 1);
            grid[newTraveler.x + base][newTraveler.y + base] = 0;
        }
    }
    else if (edge == longestEdge)
    {
        if (traveler.x == 0 && traveler.y == 0)
        {
            for (int i = 0; i < edge; i++)
                cout << headingText[golygons[i]];
            cout << endl;
            numberOfGolygons++;
        }
    }
    else
    {
        int turn1 = turn[heading][0];

        point end1;
        end1.x = traveler.x + direction[turn1][0] * (edge + 1);
        end1.y = traveler.y + direction[turn1][1] * (edge + 1);

        if (blocked(traveler, end1) == false && grid[end1.x + base][end1.y + base] == 0)
        {
            grid[end1.x + base][end1.y + base] = 1;
            golygons[edge] = turn1;
            dfs(end1, turn1, edge + 1);
            grid[end1.x + base][end1.y + base] = 0;
        }
        
        int turn2 = turn[heading][1];
        point end2;
        end2.x = traveler.x + direction[turn2][0] * (edge + 1);
        end2.y = traveler.y + direction[turn2][1] * (edge + 1);
        
        if (blocked(traveler, end2) == false && grid[end2.x + base][end2.y + base] == 0)
        {
            grid[end2.x + base][end2.y + base] = 1;
            golygons[edge] = turn2;
            dfs(end2, turn2, edge + 1);
            grid[end2.x + base][end2.y + base] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int cases, numberOfBlocks, x, y;
    cin >> cases;
    while (cases--)
    {
        cin >> longestEdge;

        int numberOfBlocks, x, y;

        blocks.clear();
        cin >> numberOfBlocks;
        for (int i = 1; i <= numberOfBlocks; i++)
        {
            cin >> x >> y;
            blocks.push_back((point){x, y});
        }

        point traveler;
        traveler.x = 0;
        traveler.y = 0;

        visited.clear();
        numberOfGolygons = 0;
        dfs(traveler, -1, 0);
        cout << "Found " << numberOfGolygons << " golygon(s)." << endl;
        cout << endl;
    }

    return 0;
}
