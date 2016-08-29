#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int gcd(int a, int b)
{
    int t;
    while (a % b) t = a, a = b, b = t % b;
    return b;
}

int plaincode[80], ciphercode[80];

int main(int argc, char *argv[])
{
    string letters = "_abcdefghijklmnopqrstuvwxyz.";
    
    srand(time(NULL));
    for (int cases = 1; cases <= 100; cases++)
    {
        int n = rand() % 70 + 1;
        while (true)
        {
            int k = rand() % 300 + 1;
            if (gcd(k, n) == 1)
            {
                for (int i = 0; i < n; i++)
                    plaincode[i] = rand() % 28;

                for (int i = 0; i < n; i++)
                    ciphercode[i] = (plaincode[(k * i) % n] - i + 84) % 28;
                    
                cout << k << ' ';
                for (int i = 0; i < n; i++)
                    cout << letters[ciphercode[i]];
                cout << '\n';

                break;
            }
        }
    }
    cout << 0 << '\n';
    
    return 0;
}
