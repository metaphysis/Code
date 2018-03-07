#include <iostream>

using namespace std;

void extgcd1(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd1(b, a % b, x, y);
        int t = x - a / b * y;
        x = y, y = t;
    }
}

void extgcd2(int a, int b, int &x, int &y)
{
    int x0, y0, x1, y1, r, q;

    x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    x = 0, y = 1;
    r = a % b, q = (a - r) / b;

    while (r)
    {
        x = x0 - q * x1, y = y0 - q * y1;
        x0 = x1, y0 = y1, x1 = x, y1 = y;
        a = b, b = r;
        r = a % b, q = (a - r) / b;
    }
}

int main(int argc, char *argv[])
{
    int a = 6, b = 8, x, y;
    
    extgcd2(a, b, x, y);
    
    cout << x << ' ' << y << '\n';
    
    return 0;
}
