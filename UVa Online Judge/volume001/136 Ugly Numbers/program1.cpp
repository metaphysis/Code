// Ugly Numbers
// UVa ID: 136
// Verdict: Accepted
// Submission Date: 2016-01-08
// UVa Run Time: 0.000s
// 
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef long long int bigNumber;

int main(int argc, char *argv[])
{
    int factors[3] = { 2, 3, 5 };
    set<bigNumber> uglyNumbers;
    priority_queue<bigNumber, vector<bigNumber>, greater<bigNumber>> candidates;

    candidates.push(1);

    for (int i = 1; i <= 1500; i++)
    {
        bigNumber top;
        do
        {
            top = candidates.top();
            candidates.pop();
        }
        while (uglyNumbers.count(top) > 0);

        uglyNumbers.insert(top);

        for (int j = 0; j < 3; j++)
        {
            bigNumber next = top * factors[j];
            if (uglyNumbers.count(next) == 0) candidates.push(next);
        }

        if (i == 1500)
        {
            cout << "The 1500'th ugly number is " << top << "." << endl;
            break;
        }
    }

    return 0;
}
