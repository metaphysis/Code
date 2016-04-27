// Triangular Vertices
// UVa IDs: 209
// Verdict: Accepted
// Submission Date: 2016-04-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

vector < int >rightmost, vertices, level;
int leftParent[33000], rightParent[33000];

int findLeft(int x)
{
    return x == leftParent[x] ? x : findLeft(leftParent[x]);
}

int findRight(int x)
{
    return x == rightParent[x] ? x : findRight(rightParent[x]);
}

void initialize()
{
    for (int n = 0, step = 1; (n + step) < 33000; n += step, step++)
    {
        int parent = n + step;
        rightmost.push_back(parent);
        leftParent[parent] = parent;
        for (int i = parent, j = step; (i + j) < 33000; i += j, j++)
            leftParent[i + j] = parent;
    }

    for (int n = 1, step = 0; (n + step) < 33000; n += step, step++)
    {
        int parent = n + step;
        rightParent[parent] = parent;
        for (int i = parent, j = step + 2; (i + j) < 33000; i += j, j++)
            rightParent[i + j] = parent;
    }
}

bool triangle()
{
    if (level[1] == level[2])
    {
        if ((level[1] - level[0]) != (vertices[2] - vertices[1]))
            return false;
        if (findLeft(vertices[0]) != findLeft(vertices[1]))
            return false;
        if (findRight(vertices[0]) != findRight(vertices[2]))
            return false;
        return true;
    }
    else if (level[0] == level[1])
    {
        if ((level[2] - level[0]) != (vertices[1] - vertices[0]))
            return false;
        if (findRight(vertices[0]) != findRight(vertices[2]))
            return false;
        if (findLeft(vertices[1]) != findLeft(vertices[2]))
            return false;
        return true;
    }

    return false;
}

bool parallelogram()
{
    if (level[0] == level[1] && level[2] == level[3])
    {
        if ((vertices[1] - vertices[0]) != (vertices[3] - vertices[2]))
            return false;
        if ((vertices[1] - vertices[0]) != (level[2] - level[0]))
            return false;
        if (findLeft(vertices[0]) == findLeft(vertices[2]))
            return true;
        if (findRight(vertices[0]) == findRight(vertices[2]))
            return true;
        return false;
    }
    else if (level[1] == level[2])
    {
        if ((level[1] - level[0]) != (vertices[2] - vertices[1]))
            return false;
        if ((level[3] - level[1]) != (vertices[2] - vertices[1]))
            return false;
        if (findLeft(vertices[0]) != findLeft(vertices[1]))
            return false;
        if (findRight(vertices[1]) != findRight(vertices[3]))
            return false;
        return true;
    }
    return false;
}

bool hexagon()
{
    if (level[0] != level[1] || level[2] != level[3] || level[4] != level[5])
        return false;
    if ((vertices[1] - vertices[0]) != (vertices[5] - vertices[4]))
        return false;
    if ((vertices[1] - vertices[0]) != (level[2] - level[0]))
        return false;
    if ((vertices[1] - vertices[0]) != (level[4] - level[2]))
        return false;
    if ((vertices[3] - vertices[2]) != 2 * (vertices[1] - vertices[0]))
        return false;
    if (findLeft(vertices[0]) != findLeft(vertices[2]))
        return false;
    if (findRight(vertices[2]) != findRight(vertices[4]))
        return false;
    return true;
}

void analyze(string line)
{
    cout << line;

    level.clear();
    for (int i = 0; i < vertices.size(); i++)
        level.push_back(lower_bound(rightmost.begin(), rightmost.end(),
                vertices[i]) - rightmost.begin() + 1);

    if (vertices.size() == 3 && triangle())
        cout << " are the vertices of a triangle\n";
    else if (vertices.size() == 4 && parallelogram())
        cout << " are the vertices of a parallelogram\n";
    else if (vertices.size() == 6 && hexagon())
        cout << " are the vertices of a hexagon\n";
    else
        cout << " are not the vertices of an acceptable figure\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);

    initialize();

    string line;
    while (getline(cin, line))
    {
        vertices.clear();

        int index;
        istringstream iss(line);
        while (iss >> index)
            vertices.push_back(index);

        sort(vertices.begin(), vertices.end());
        int n = unique(vertices.begin(), vertices.end()) - vertices.begin();

        if (n != vertices.size())
            cout << line << " are not the vertices of an acceptable figure\n";
        else
            analyze(line);
    }

    return 0;
}
