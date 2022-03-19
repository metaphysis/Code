#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    double number = 1.005;
    
    cout << fixed << setprecision(2) << number << endl;
    cout << fixed << setprecision(2) << (number + EPSILON) << endl;
    
    return 0;
}
