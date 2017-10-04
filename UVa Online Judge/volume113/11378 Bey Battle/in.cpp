#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    cout << "100000\n";
    for (int c = 1; c <= 100000; c++)
    {
        int n = rand() % 1000000;
        if (rand() % 2 == 0)
            cout << n;
        else
            cout << -n;
        cout << ' ';
        n = rand() % 1000000;
        if (rand() % 2 == 0)
            cout << n;
        else
            cout << -n;
        cout << '\n';
    }
}
