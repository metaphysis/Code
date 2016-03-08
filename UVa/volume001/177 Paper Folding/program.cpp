// Paper Folding
// UVa IDs: 177
// Verdict: Accepted
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

const int SIDE = 1024;

char oldMatrix[SIDE][SIDE] = { 0 }, newMatrix[SIDE][SIDE] = { 0 };

int rotateX, rotateY;
int startX, startY;


void rotate()
{
    memset(newMatrix, 0, sizeof(newMatrix));
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
        {
            newMatrix[i][j] = oldMatrix[j][SIDE - 1 - i];
            if (newMatrix[i][j] == 0)
                continue;
                
            if (newMatrix[i][j] == '_')
                newMatrix[i][j] = '|';
            else
                newMatrix[i][j] = '_';
        }
}

void merge()
{
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            oldMatrix[i][j] += newMatrix[i][j];
}

void unfolding(int n)
{
    if (n > 1)
    {
        unfolding(n - 1);
        rotate();
        merge();
    }
    else
    {
        startX = 0;
        startY = 0;
        rotateX = 1;
        rotateY = 0;
        oldMatrix[0][0] = '_';
    }
}

void display()
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            if (oldMatrix[i][j] > 0)
                cout << oldMatrix[i][j];
    }
    
    cout << "\n^\n";
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        memset(oldMatrix, 0, sizeof(oldMatrix));

        unfolding(n);
        
        display();
    }
    
	return 0;
}
