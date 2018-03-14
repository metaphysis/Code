#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    
    bool operator == (point p)
    {
        return x == p.x && y == p.y;
    }
};

int main(int argc, char *argv[])
{
    srand(time(NULL));

    for (int c = 1; c <= 25; c++)
    {
        int N = rand() % 297 + 2;
        cout << N << '\n';
        
        vector<point> points;
        
        int vertices = 1;
        while (vertices < N)
        {
            int x = rand() % 300, y = rand() % 300;
            if (rand() % 2 == 0) x *= -1;
            if (rand() % 2 == 0) y *= -1;
            if (find(points.begin(), points.end(), point{x, y}) != points.end()) continue;
            if (vertices > 0) cout << ' ';
            cout << x << ' ' << y;
            points.push_back(point{x, y});
            vertices++;
        }
        
        cout << ' ' << points.front().x << ' ' << points.front().y << '\n';
    }
    
    cout << "0\n";
    
    return 0;
}
