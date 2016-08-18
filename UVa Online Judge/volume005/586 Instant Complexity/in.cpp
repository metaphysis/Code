#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_CASES = 100, MAX_OP = 60, MAX_STACK = 10, BASE = 10;

int main(int argc, char *argv[])
{
    cout << MAX_CASES << "\n\n";
    
    srand(time(NULL));
    
    for (int c = 1; c <= MAX_CASES; c++)
    {
        if (c > 1)
            cout << '\n';
            
        int ops = 1, stack = 0;
        
        cout << "BEGIN\n";
        while (ops < MAX_OP)
        {
            if (rand() % 2 + 1 > 1 && stack < MAX_STACK)
            {
                stack++;
                cout << "LOOP ";
                if (rand() % 10 > 3)
                    cout << 'n';
                else
                    cout << rand() % BASE;
            }
            else
            {
                cout << "OP ";
                cout << rand() % BASE;
            }
            
            cout << '\n';
            
            if (stack > 0)
            {
                if (rand() % 10 > 7)
                {
                    cout << "END\n";
                    stack--;
                }
            }
            
            ops++;
        }
        
        while (stack > 0)
        {
            cout << "END\n";
            stack--;
        }
        
        cout << "END\n";
    }
    
    return 0;
}
