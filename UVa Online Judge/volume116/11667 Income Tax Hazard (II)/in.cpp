#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int i = 1; i <= 1000; i++)
    {
        cout << (rand() % 400000 + 1) << ' ';
        int S1 = rand() % 150000 + 50000;
        cout << S1 << ' ' << (S1 + rand() % (200000 - S1)) << '\n';
    }
    cout << "0 0 0\n";

    return 0;
}
