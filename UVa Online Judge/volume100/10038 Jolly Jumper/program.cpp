// Jolly Jumpers （快乐的跳跃者）
// PC/UVa IDs: 110201/10038, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    int number[3001], n;
    bool isJolly;

    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> n;

        if (n <= 0)
            isJolly = false;
        else if (n == 1)
            isJolly = true;
        else
        {
            for (int i = 0; i < n; i++)
                iss >> number[i];
            for (int i = 0; i < (n - 1); i++)
                number[i] = abs(number[i + 1] - number[i]);

            sort(number, number + n - 1);
            int size = unique(number, number + n - 1) - number;
            isJolly = ((n - 1) == size && number[size - 1] == (n - 1));
        }

        cout << (isJolly ? "Jolly" : "Not jolly") << endl;
    }
}
