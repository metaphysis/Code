// Da Vinci Code
// UVa ID: 11385
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 45;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int fibs[MAXN] = {1, 2};
    map<int, int> indexer;
    for (int i = 2; i < MAXN; i++) fibs[i] = fibs[i - 1] + fibs[i - 2];
    for (int i = 0; i < MAXN; i++) indexer[fibs[i]] = i;

    int cases, n, maxLength;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        vector<int> numbers(n, 0);
        maxLength = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> numbers[i];
            maxLength = max(maxLength, numbers[i]);
        }

        cin.ignore(1024, '\n');
        getline(cin, line);
        string message;
        for (auto letter : line)
            if (isupper(letter))
                message += letter;

        string decode(indexer[maxLength] + 1, ' ');
        for (int i = 0; i < numbers.size(); i++)
            decode[indexer[numbers[i]]] = message[i];
        cout << decode << '\n';
    }

    return 0;
}
