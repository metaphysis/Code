#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    for (int c = 1; c <= 100; c++)
    {
        int l = rand() % 1000;
        int w = rand() % 1000;
        
        if (l < w) swap(l, w);
        if (l == w) l += 25;
        
        cout << l << ',' << w;
        
        for (int i = 1; i <= 20; i++)
        {
            cout << ' ';
            
            int corner = w + rand() % 1000 + 1;
            cout << corner << ',';
            corner = w + rand() % 1000 + 1;
            cout << corner;
        }
        cout << '\n';
    }

    return 0;
}
