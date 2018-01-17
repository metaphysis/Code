// Divisibility
// UVa ID: 10036
// Verdict: Accepted
// Submission Date: 2018-01-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, N, K, numbers[10010][2], modulo[10010][110] = {0}, n;

    cin >> M;
    for (int c = 1; c <= M; c++)
    {
        cin >> N >> K;
        for (int i = 0; i < N; i++)
        {
            cin >> n;
            numbers[i][0] = ((n % K) + K) % K;
            numbers[i][1] = ((-n % K) + K) % K;
        }

        for (int i = 0; i <= N; i++)
            for (int j = 0; j < K; j++)
                modulo[i][j] = 0;

        modulo[0][numbers[0][0]] = 1;
        for (int i = 1; i < N; i++)
            for (int j = 0; j < K; j++)
                if (modulo[i - 1][j])
                {
                    modulo[i][(j + numbers[i][0]) % K] = 1;
                    modulo[i][(j + numbers[i][1]) % K] = 1;
                }

        if (modulo[N - 1][0]) cout << "Divisible\n";
        else cout << "Not divisible\n";
    }

    return 0;
}
