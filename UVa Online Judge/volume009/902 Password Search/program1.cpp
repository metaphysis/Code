// Password Search
// UVa ID: 902
// Verdict: Accepted
// Submission Date: 2017-01-11
// UVa Run Time: 0.080s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

int N;
string message;

void decode(long long password)
{
    long long mask = 0x1F;
    for (int i = 2; i <= N; i++) mask <<= 5;
    for (int i = N - 1; i >= 0; i--)
    {
        cout << (char)('a' + ((password & mask) >> (5 * i)));
        mask >>= 5;
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> N >> message)
    {
        vector<long long> substring;

        long long mask = 0x1F;
        for (int i = 2; i <= N; i++) mask <<= 5, mask |= 0x1F;

        long long k = 0;
        for (int i = 0; i < N; i++) k <<= 5, k |= (message[i] - 'a');
        substring.push_back(k);

        for (int i = N; i < message.length(); i++)
        {
            k <<= 5, k &= mask, k |= (message[i] - 'a');
            substring.push_back(k);
        }

        sort(substring.begin(), substring.end());

        int most = 0, frequency = 0;
        long long password = -1, head = -1;

        for (auto sub : substring)
        {
            if (sub == head) frequency++;
            else
            {
                if (frequency > most) most = frequency, password = head;
                if (password == -1) password = sub;
                head = sub, frequency = 1;
            }
        }

        decode(password);
    }

    return 0;
}
