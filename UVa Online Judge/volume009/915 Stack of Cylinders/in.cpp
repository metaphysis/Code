#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_CASES = 100;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int c = 1; c <= MAX_CASES; c++)
    {
        int circles = rand() % 90 + 10;
        
        cout << circles << '\n';
        
        for (int i = 1; i <= circles; i++)
        {
            int radius = rand() % 1000 + 3;
            cout << radius << '\n';
        }
    }
    
    return 0;
}
