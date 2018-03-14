#include <bits/stdc++.h>

using namespace std;

int main(int argc, char * argv[])
{
    srand(time(NULL));
    
    for (int c = 1; c <= 100; c++)
    {
        int n = 30;
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
        {
            if ((rand() % 2) == 1)
            {
                int x = rand() % 1000, y1 = rand() % 1000, y2 = rand() % 1000;
                while (y2 == y1)
                    y2 = rand() % 1000;
                cout << x << ' ' << y1 << ' ' << x << ' ' << y2 << '\n';
            }
            else
            {
                int y = rand() % 1000, x1 = rand() % 1000, x2 = rand() % 1000;
                while (x2 == x1)
                    x2 = rand() % 1000;
                cout << x1 << ' ' << y << ' ' << x2 << ' ' << y << '\n';
            }
        }
    }
    cout << "0\n";
    return 0;
}
