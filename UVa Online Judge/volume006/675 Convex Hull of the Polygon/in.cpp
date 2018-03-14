#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int x, y;
    for (int c = 1; c <= 10; c++)
    {
        if (c > 1) cout << '\n';
        for (int i = 1; i <= 1000; i++)
        {
            x = rand() % 1000 * (rand() % 2 == 0 ? 1 : -1);
            y = rand() % 1000 * (rand() % 2 == 0 ? 1 : -1);
            cout << x << ", " << y << '\n';
            if (rand() % 100 >= 60) cout << x << ", " << y << '\n';
        }
    }
    
    return 0;
}
