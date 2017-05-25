#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int cases = 20;
    set<long long int> produced;
    
    for (int c = 1; c <= cases; c++)
    {
        int n = rand() % 1000 + 1;
        cout << n << '\n';

        produced.clear();
        int counter = 0;
        while (counter < n)
        {
            long long int x = rand() % 1000;
            long long int y = rand() % 1000;
            int brightness = rand() % 100;
            long long int hash = x * 10000 + y;
            if (produced.find(hash) == produced.end())
            {
                cout << x << ' ' << y << ' ' << brightness << '\n';
                produced.insert(hash);
                counter++;
            }
        }
        
        int m = rand() % 20 + 1;
        cout << m << '\n';
        
        for (int i = 1; i <= m; i++)
        {
            int si = rand() % 6 + 1;
            string name = to_string(c) + "-" + to_string(i);
            cout << si << ' ' << name << '\n';
            
            produced.clear();
            counter = 0;
            while (counter < si)
            {
                long long int x = rand() % 1000;
                long long int y = rand() % 1000;
                long long int hash = x * 10000 + y;
                if (produced.find(hash) == produced.end())
                {
                    cout << x << ' ' << y << '\n';
                    produced.insert(hash);
                    counter++;
                }
            }
        }
    }
    cout << 0 << endl;

    return 0;
}
