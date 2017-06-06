#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int gcd(int a, int b)
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int c = 1; c <= 10000; c++)
    {
        int screen_width = rand() % 10000 + 1;
        int screen_height = rand() % 10000 + 1;
        
        cout << screen_width << ' ' << screen_height;
        
        vector<pair<int, int>> rectangle(4);
        
        int width[4], height[4];
        
        switch (rand() % 9)
        {
            case 0:
                width[0] = rand() % 1000 + 1, height[0] = rand() % 1000 + 1;
                if (width[0] < screen_width)
                {
                    width[1] = screen_width - width[0];
                    height[1] = rand() % 1000 + 1;
                }
                else
                {
                    width[1] = rand() % 1000 + 1;
                    height[1] = rand() % 1000 + 1;
                }
                
                if (height[0] < screen_height)
                {
                    width[2] = rand() % 1000 + 1;
                    height[2] = screen_height - height[0];
                }
                else
                {
                    width[2] = rand() % 1000 + 1;
                    height[2] = rand() % 1000 + 1;
                }
                
                if (width[2] < screen_width && height[1] < screen_height)
                {
                    width[3] = screen_width - width[2];
                    height[3] = screen_height - height[1];
                }
                else
                {
                    width[3] = rand() % 1000 + 1;
                    height[3] = rand() % 1000 + 1;
                }
            break;
            case 1:
            
            break;
            case 2:
            
            break;
            case 3:
            
            break;
            case 4:
            
            break;
            case 5:
            
            break;
            case 6:
            
            break;
            case 7:
            
            break;
            case 8:
            
            break;
        }
        
        for (int i = 0; i < 4; i++)
            rectangle[i].first = width[i], rectangle[i].second = height[i];
            
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(rectangle.begin(), rectangle.end(), default_random_engine(seed));
        for (int i = 0; i < 4; i++)
        {
            int divisor = gcd(rectangle[i].first, rectangle[i].second);
            cout << ' ' << rectangle[i].first / divisor << ' ' << rectangle[i].second / divisor;
        }
        cout << '\n';
    }
    
    cout << "0 0\n";

    return 0;
}
