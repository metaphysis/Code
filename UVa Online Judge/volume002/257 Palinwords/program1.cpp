// Palinwords
// UVa ID: 257
// Verdict: Accepted
// Submission Date: 2016-05-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int P[10240];

bool manacher(string word)
{
    for (int i = word.length() - 1; i >= 0; i--)
        word.insert(word.begin() + i, '#');        
    word.push_back('|');
    word.front() = '$';

    set<string> palindromes;

    int center = 0, rightmost = 0;
    for (int i = 1; i < word.size(); i++)
    {
        int x = 2 * center - i, y = rightmost - i;
        P[i] = (rightmost > i) ? (P[x] < y ? P[x] : y) : 1;
        while (word[i - P[i]] == word[i + P[i]]) P[i]++;
        if (i + P[i] > rightmost)
        {
            center = i;
            rightmost = i + P[i];
        }
        
        if (P[i] >= 3)
        {
            string palindrome;
            if (isalpha(word[i]))
                palindrome += word[i];

            for (int j = i + 1; j <= (i + P[i] - 1); j++)
                if (isalpha(word[j]))
                {
                    palindrome += word[j];
                    palindrome.insert(palindrome.begin(), word[j]);

                    if (palindrome.length() >= 5)
                        break;

                    if (palindrome.length() >= 3)
                    {
                        if (palindromes.count(palindrome) > 0)
                            continue;

                        for (auto it = palindromes.begin(); it != palindromes.end(); it++)
                            if (palindrome.find(*it) == palindrome.npos &&
                                (*it).find(palindrome) == palindrome.npos)
                                    return true;

                        palindromes.insert(palindrome);
                    }
                }
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
            continue;

        string word;
        istringstream iss(line);
        while (iss >> word)
            if (manacher(word))
                cout << word << endl;
    }

    return 0;
}
