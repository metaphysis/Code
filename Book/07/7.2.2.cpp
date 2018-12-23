void extgcd(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd(b, a % b, x, y);
        int t = x - a / b * y;
        x = y, y = t;
    }
}

void extgcd(int a, int b, int &x, int &y)
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
