#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int numerator, denominator;
    while (cin >> numerator >> denominator, denominator > 0)
    {
        cout << '[' << numerator / denominator;
        numerator %= denominator;
        
        bool printComma = false;
        while (numerator > 0)
        {
            if (printComma)
                cout << ',';
            else
            {
                cout << ';';
                printComma = true;
            }

            swap(numerator, denominator);
            cout << numerator / denominator;
            numerator %= denominator;
        }
        cout << "]\n";
    }

    return 0;
}
