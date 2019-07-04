#include <bits/stdc++.h>

using namespace std;

struct point { int x, y; } ps[210];

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 100 + 1;
        cout << n << '\n';
        n *= 2;
        for (int i = 0; i < n; i++)
        {
            while (true)
            {
                int x = rand() % 10001;
                int y = rand() % 10001;
                if (rand() % 2) x *= -1;
                if (rand() % 2) y *= -1;
                bool flag = true;
                for (int j = 0; j < i; j++)
                    for (int k = j + 1; k < i; k++)
                        if ((ps[k].x - ps[j].x) * (y - ps[j].y) - (x - ps[j].x) * (ps[k].y - ps[j].y) == 0)
                        {
                            flag = false;
                            break;
                        }
                if (flag) 
                {
                    ps[i].x = x, ps[i].y = y;
                    cout << x << ' ' << y << '\n';
                    break;
                }
            }
                    
        }
    }
}
