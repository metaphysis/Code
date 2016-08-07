int gcd(int a, int b)
{
    int t;
    while (a % b) t = a, a = b, b = t % b;
    return b;
}
