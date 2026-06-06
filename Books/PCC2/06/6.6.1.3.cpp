const int MAXF = 64;
long long fibs[MAXF] = {1, 2};

string getFinary(long long n)
{
    for (int i = 2; i < MAXF; i++) fibs[i] = fibs[i - 1] + fibs[i - 2];
    bitset<64> finary(0);
    while (n)
    {
        for (int i = MAXF - 1; i >= 0; i--)
            if (n >= fibs[i])
            {
                finary.set(i);
                n -= fibs[i];
                break;
            }
    }
    string f = finary.to_string();
    while (f.size() && f.front() == '0') f.erase(f.begin());
    return f;
}
