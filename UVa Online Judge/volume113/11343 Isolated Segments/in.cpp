#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    cout << 1000 << '\n';
    for (int c = 1; c <= 1000; c++)
    {
        int M = rand() % 101;
        cout << M << '\n';
        for (int i = 0; i < M; i++)
        {
            int px = rand() % 1000, py = rand() % 1000;
            int ex = rand() % 1000, ey = rand() % 1000;
            if (rand() % 2) px *= -1;
            if (rand() % 2) py *= -1;
            if (rand() % 2) ex *= -1;
            if (rand() % 2) ey *= -1;
            cout << px << ' ' << py << ' ' << ex << ' ' << ey << '\n';
        }
    }
    return 0;
}
