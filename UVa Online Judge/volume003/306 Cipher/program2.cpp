// Cipher
// UVa IDs: 306
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int key[210], cycle[210], permutation[210][210], n, k;
char message[210], ciphered[210];

void findCycle()
{
    for (int i = 1; i <= n; i++)
    {
        int length = 1;
        permutation[i][length] = key[i];
        for (int j = key[i]; j != i; j = key[j], permutation[i][length] = j) length++;
        permutation[i][0] = permutation[i][length];
        cycle[i] = length;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++) cin >> key[i];

        while (cin >> k, k)
        {
            cin.getline(message, 210);

            int number = 1;
            while (message[number] != '\0') number++;
            while (number <= n) message[number++] = ' ';
            message[number] = '\0';

            findCycle();

            for (int i = 1; i <= n; i++) ciphered[permutation[i][k % cycle[i]]] = message[i];
            for (int i = 1; i <= n; i++) cout << ciphered[i];

            cout << "\n";
        }

        cout << "\n";
    }

    return 0;
}
