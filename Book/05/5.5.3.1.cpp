#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    double lower = -2.0, upper = 1.0, step = 0.05;
    double epsilon = 1e-7;
    
    int steps1 = 0, steps2 = 0;
    for (double i = lower; i <= upper; i += step) steps1++;
    for (double j = lower; j <= upper + epsilon; j += step) steps2++;
    
    cout << "steps1 = " << steps1 << " steps2 = " << steps2 << endl;    
    
    return 0;
}
