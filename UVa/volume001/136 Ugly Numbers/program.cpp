// Ugly Numbers
// UVa IDs: 136
// Verdict: Accepted
// Submission Date: 2016-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    long long int start = 1;
    int counter = 1;

    while (counter < 1500)
    {
        start++;
        long long int number = start;
        while (number % 2 == 0) number /= 2;
        while (number % 3 == 0) number /= 3;
        while (number % 5 == 0) number /= 5;
        if (number == 1) counter++;
    }

    cout << "The 1500'th ugly number is " << start << "." << endl;

    return 0;
}
