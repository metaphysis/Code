// Triangular Vertices
// UVa ID: 209
// Verdict: Accepted
// Submission Date: 2016-04-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector < int > vertices, levels;
int principal[33000], secondary[33000], level[33000];

void makeSet()
{
    for (int n = 1, step = 0; (n + step) < 33000; n += step, step++)
    {
        int parent = n + step;
        principal[parent] = parent;
        for (int i = parent, j = step + 2; (i + j) < 33000; i += j, j++)
            principal[i + j] = parent;
    }
    
    for (int n = 0, step = 1; (n + step) < 33000; n += step, step++)
    {
        int parent = n + step;
        secondary[parent] = parent;
        for (int i = parent, j = step; (i + j) < 33000; i += j, j++)
            secondary[i + j] = parent;
    }
    
    for (int n = 1, step = 1; n < 33000; step++)
        for (int i = 1; i <= step && n < 33000; i++)
            level[n++] = step;
}

bool triangle()
{
    if (levels[1] == levels[2])
    {
        if (secondary[vertices[0]] != secondary[vertices[1]])
            return false;
        if (principal[vertices[0]] != principal[vertices[2]])
            return false;
        return true;
    }
    else if (levels[0] == levels[1])
    {
        if (principal[vertices[0]] != principal[vertices[2]])
            return false;
        if (secondary[vertices[1]] != secondary[vertices[2]])
            return false;
        return true;
    }

    return false;
}

bool parallelogram()
{
    if (levels[0] == levels[1] && levels[2] == levels[3])
    {
        if ((vertices[1] - vertices[0]) != (vertices[3] - vertices[2]))
            return false;
        if ((vertices[1] - vertices[0]) != (levels[2] - levels[0]))
            return false;
        if (secondary[vertices[0]] == secondary[vertices[2]])
            return true;
        if (principal[vertices[0]] == principal[vertices[2]])
            return true;
        return false;
    }
    else if (levels[1] == levels[2])
    {
        if ((levels[1] - levels[0]) != (vertices[2] - vertices[1]))
            return false;
        if ((levels[3] - levels[1]) != (vertices[2] - vertices[1]))
            return false;
        if (secondary[vertices[0]] != secondary[vertices[1]])
            return false;
        if (principal[vertices[1]] != principal[vertices[3]])
            return false;
        return true;
    }
    return false;
}

bool hexagon()
{
    if (levels[0] != levels[1] || levels[2] != levels[3] || levels[4] != levels[5])
        return false;
    if ((vertices[1] - vertices[0]) != (vertices[5] - vertices[4]))
        return false;
    if ((vertices[1] - vertices[0]) != (levels[2] - levels[0]))
        return false;
    if ((vertices[1] - vertices[0]) != (levels[4] - levels[2]))
        return false;
    if ((vertices[3] - vertices[2]) != 2 * (vertices[1] - vertices[0]))
        return false;
    if (secondary[vertices[0]] != secondary[vertices[2]])
        return false;
    if (principal[vertices[2]] != principal[vertices[4]])
        return false;
    return true;
}

void analyze(string line)
{
    cout << line;

    levels.clear();
    for (int i = 0; i < vertices.size(); i++)
        levels.push_back(level[vertices[i]]);

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
    makeSet();

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
