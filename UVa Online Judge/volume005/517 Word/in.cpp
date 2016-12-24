#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    string rule[8] = {"aaa", "aab", "aba", "abb", "baa", "bab", "bba", "bbb"};
    
    for (int c = 1; c <= 100; c++)
    {
        int n = rand() % 16;
        if (n <= 3) n = 3;
        
        cout << n << '\n';
        for (int i = 1; i <= n; i++)
            cout << (char)('a' + rand() % 2);
        cout << '\n';
        
        for (int i = 0; i < 8; i++)
        {
            cout << rule[i] << (char)('a' + rand() % 2) << '\n';
        }
        
        cout << rand() % 2000000000 << '\n';
    }
    
    return 0;
}
