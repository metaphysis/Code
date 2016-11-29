#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int c = 1; c <= 100; c++)
    {
        int n = rand() % 21;
        cout << n << '\n';
        cout << (rand() % 1000) << ' ' << (rand() % 10) << ' ';
        cout << (rand() % 1000) << ' ' << (990 + rand() % 10) << '\n';
        for (int r = 1; r <= n; r++)
        {
            int x = 10 + rand() % 800, width = rand() % 90 + 1;
            int y = 10 + rand() % 800, height = rand() % 90 + 1;
            cout << x << ' ' << y << ' ' << (x + width) << ' ' << y << ' ';
            cout << x << ' ' << (y + height) << '\n';
        }
    }
    cout << "-1\n";
}
