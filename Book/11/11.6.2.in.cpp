#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int cases = 1000, up = 400;
    for (int cs = 1; cs <= cases; cs++)
    {
        int C = rand() % 100 + 1;
        cout << C;
        for (int c = 1; c <= C; c++)
        {
            int d = rand() % 400 + 1;
            cout << ' ' << d;
        }
        int M = rand() % 10000 + 1;
        cout << ' ' << M / 100 << '.' << M % 100 << '\n';
    }
    cout << 0 << '\n';

    return 0;
}
