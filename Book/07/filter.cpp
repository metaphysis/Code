#include <iostream>

using namespace std;

const int LIMITS = 1000000;

bool prime[LIMITS];

void filter()
{
    prime[0] = prime[1] = false;

    for (int i = 2; i < LIMITS; i++)
        prime[i] = true;

    for (int i = 2; i < LIMITS; i++)
        if (prime[i])
            for (int j = 2 * i; j < LIMITS; j += i)
                prime[j] = false;
}

int main(int argc, char *argv[])
{
    filter();

    int counter = 0;
    for (int i = 0; i < LIMITS; i++)
    {
        if (prime[i])
            cout << i << " ";

        if (++counter % 100 == 0)
            cout << "\n";
    }
    return 0;
}
