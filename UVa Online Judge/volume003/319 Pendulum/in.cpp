#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int cases = 1000, x1, y1;
    for (int c = 1; c <= cases; c++)
    {
        int n = rand() % 100;
        int lengthOfString = rand() % 10000 + 1;
        
        cout << n << ' ' << lengthOfString << '\n';
        
        map<int, map<int, bool>> cache;
        cache[0][0] = true;
        for (int i = 1; i <= n; i++)
        {
            do
            {
                x1 = rand() % 100;
                if (rand() % 2 == 0) x1 *= -1;
                y1 = rand() % 100;
                y1 *= -1;
            } while (cache.find(x1) != cache.end() && cache[x1].find(y1) != cache[x1].end());
            
            cout << x1 << ' ' << y1 << '\n';
            cache[x1][y1] = true;
        }
    }
    
    cout << "0 0\n";
    return 0;
}

