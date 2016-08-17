#include <iostream>

using namespace std;

const int MAX_N = 1000000;

int primes[MAX_N + 1] = { 0 }, prime_count = 0;

void filter()
{
    for (int i = 2; i <= MAX_N; i++)
        if (!primes[i])
        {
            for (int j = 2 * i; j <= MAX_N; j += i)
                primes[j] = 1;
            primes[prime_count++] = i;
        }
}

int main(int argc, char *argv[])
{
    filter();

    for (int i = 0; i < prime_count; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
