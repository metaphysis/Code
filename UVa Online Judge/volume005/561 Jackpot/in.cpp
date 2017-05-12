#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int cases = 100;
    cout << cases << '\n';
    
    for (int c = 1; c <= cases; c++)
    {
        int x = rand() % 198 + 3;
        int y = rand() % 198 + 3;
        int z = rand() % 198 + 3;
        
        cout << x << ' ' << y << ' ' << z << '\n';
        
        for (int i = 1; i <= x; i++)
        {
            int k = rand() % 26;
            cout << (char)('A' + k);
        }
        cout << '\n';
        for (int i = 1; i <= y; i++)
        {
            int k = rand() % 26;
            cout << (char)('A' + k);
        }
        cout << '\n';
        for (int i = 1; i <= z; i++)
        {
            int k = rand() % 26;
            cout << (char)('A' + k);
        }
        cout << '\n';        
    }
    
    return 0;
}
