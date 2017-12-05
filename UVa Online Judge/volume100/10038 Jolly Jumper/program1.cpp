// Jolly Jumpers （快乐的跳跃者）
// PC/UVa IDs: 110201/10038, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2017-02-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);

    int number[3010], tag[3010], n;
    bool is_jolly;

    while (cin >> n)
    {
        is_jolly = true;
        if (n == 0)
            is_jolly = false;
        else if (n == 1)
        {
            cin >> n;
            is_jolly = true;
        }
        else
        {
            for (int i = 0; i < n; i++)
                cin >> number[i];
            
            memset(tag, 0, sizeof(tag));
            for (int i = 0; i < (n - 1); i++)
                tag[abs(number[i + 1] - number[i])] = 1;

            for (int i = 1; i <= n - 1; i++)
                if (!tag[i])
                {
                    is_jolly = false;
                    break;
                }
        }

        cout << (is_jolly ? "Jolly" : "Not jolly") << '\n';
    }
}
