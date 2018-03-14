#include <bits/stdc++.h>

using namespace std;

int fee(int watt)
{
    int cost = 0;
    if (watt > 1000000) { cost += (watt - 1000000) * 7; watt = 1000000; }
    if (watt >= 10001) { cost += (watt - 10000) * 5; watt = 10000; }
    if (watt >= 101) { cost += (watt - 100) * 3; watt = 100; }
    cost += watt * 2;
    return cost;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int watta, wattb, feea, feeb;
    for (int i = 1; i <= 100; i++)
    {
        do
        {
            watta = rand() % 100000000 + 1;
            feea = fee(watta);
            wattb = rand() % 100000000 + 1;
            feeb = fee(wattb);
        } while (fee(watta + wattb) > 1e9);
        
        cout << fee(watta + wattb) << ' ' << abs(feea - feeb) << '\n';
    }
    cout << "0 0\n";

    return 0;
}
