// All Squares
// UVa ID: 155
// Verdict: Accepted
// Submission Date: 2016-02-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 题目描述似乎有问题。

#include <iostream>
#include <iomanip>

using namespace std;

int x, y;
int counter;

bool pointInSquare(int centerx, int centery, int size)
{
    return (centerx - size <= x) && (x <= centerx + size) 
        && (centery - size <= y) && (y <= centery + size);
}

void generateSquare(int k, int centerx, int centery)
{
    int side = k;
    if (pointInSquare(centerx, centery, side))
        counter++;

    if (k > 1)
    {
        k /= 2;
        
        generateSquare(k, centerx - side, centery - side);
        generateSquare(k, centerx + side, centery - side);
        generateSquare(k, centerx + side, centery + side);
        generateSquare(k, centerx - side, centery + side);
    }
}

int main(int argc, char* argv[])
{
    int k;
    while (cin >> k >> x >> y, k || x || y)
    {
        counter = 0;
        generateSquare(k, 1024, 1024);
        cout << setw(3) << right << counter << endl;
    }
    
	return 0;
}
