// The Vigenère Cipher
// UVa ID: 856
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<string> numbers;
    string digit[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 999; i >= 0; i--)
    {
        string text;
        int n = i, cnt = 0;
        while (cnt++ < 3)
        {
            text.insert(0, digit[n % 10]);
            n /= 10;
        }
        numbers.push_back(text);
    }
    
    int cases = 0;
    string line;
    while (cin >> line)
    {
        if (cases++ > 0) cout << '\n';
        for (int i = 0; i < numbers.size(); i++)
        {
            if (line.length() != numbers[i].length()) continue;
            for (int j = 0; j < line.length(); j++)
            {
                char c = 'a' + (line[j] - 'B' + 26) % 26;
                cout << (char)('A' + (c - numbers[i][j] + 26) % 26);
            }
            cout << " -> " << numbers[i] << '\n';
        }
    }

    return 0;
}
