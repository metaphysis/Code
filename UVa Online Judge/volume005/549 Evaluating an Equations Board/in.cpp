#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    char symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', 'x'};

    for (int i = 1; i <= 1000; i++)
    {
        int goal = rand() % 100;
        int numberOfSymbols = (goal >= 10 ? 11 : 12);
        for (int j = 1; j <= numberOfSymbols; j++)
            cout << symbols[rand() % 13];
        cout << '\n';
        cout << goal << '\n';
    }
    
    return 0;
}
