#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int c = 1; c <= 1000; c++)
    {
        int L = rand() % 1001, W = rand() % 1001, H = rand() % 1001;
        int x1, y1, z1, x2, y2, z2;
        
        int plane1 = rand() % 6;
        switch (plane1)
        {
            // top
            case 0:
            x1 = rand() % (L + 1), y1 = rand() % (W + 1), z1 = H;
            break;
            
            // left
            case 1:
            x1 = rand() % (L + 1), y1 = 0, z1 = rand() % (H + 1);
            break;
            
            // right
            case 2:
            x1 = rand() % (L + 1), y1 = W, z1 = rand() % (H + 1);
            break;
            
            // front
            case 3:
            x1 = L, y1 = rand() % (W + 1), z1 = rand() % (H + 1);
            break;
            
            // back
            case 4:
            x1 = 0, y1 = rand() % (W + 1), z1 = rand() % (H + 1);
            break;
            
            // bottom
            case 5:
            x1 = rand() % (L + 1), y1 = rand() % (W + 1), z1 = 0;
            break;
        }
        
        int plane2 = rand() % 6;
        switch (plane2)
        {
            // top
            case 0:
            x2 = rand() % (L + 1), y2 = rand() % (W + 1), z2 = H;
            break;
            
            // left
            case 1:
            x2 = rand() % (L + 1), y2 = 0, z2 = rand() % (H + 1);
            break;
            
            // right
            case 2:
            x2 = rand() % (L + 1), y2 = W, z2 = rand() % (H + 1);
            break;
            
            // front
            case 3:
            x2 = L, y2 = rand() % (W + 1), z2 = rand() % (H + 1);
            break;
            
            // back
            case 4:
            x2 = 0, y2 = rand() % (W + 1), z2 = rand() % (H + 1);
            break;
            
            // bottom
            case 5:
            x2 = rand() % (L + 1), y2 = rand() % (W + 1), z2 = 0;
            break;
        }
        
        cout << L << ' ' << W << ' ' << H << ' ';
        cout << x1 << ' ' << y1 << ' ' << z1 << ' ';
        cout << x2 << ' ' << y2 << ' ' << z2 << '\n';
    }
    
    return 0;
}
<<<<<<< HEAD


=======
>>>>>>> 0070ff72a5e944aa9876788eb3144e2545a171b3
