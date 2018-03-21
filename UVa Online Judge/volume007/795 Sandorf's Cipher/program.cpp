// Sandorf's Cipher
// UVa ID: 795
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int mapping[36] = {
    1, 3, 5, 10, 14, 19, 22, 29, 33,
    8, 11, 15, 18, 23, 26, 28, 31, 35,
    2, 6, 13, 16, 21, 25, 30, 32, 34,
    0, 4, 7, 9, 12, 17, 20, 24, 27
};

string decode(string encrypted)
{
    string message;
    for (int i = 0; i < encrypted.length(); i += 36)
    {
        string square = encrypted.substr(i, 36);
        string decrypted;
        for (int i = 0; i < 36; i++)
            decrypted += square[mapping[i]];
        while (decrypted.front() == '#') decrypted.erase(decrypted.begin());
        reverse(decrypted.begin(), decrypted.end());
        message.insert(0, decrypted);
    }
    return message;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string line;
    while (getline(cin, line))
    {
        if (cases++ > 0) cout << '\n';
        cout << decode(line) << '\n';
        while (getline(cin, line), line.length() > 0)
            cout << decode(line) << '\n';
    }

    return 0;
}
