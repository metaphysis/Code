// Palinwords
// UVa ID: 257
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

bool manacher(string word)
{
    for (int i = word.length() - 1; i >= 0; i--)
        word.insert(word.begin() + i, '#');
    word.push_back('#');

    //cout << word << endl;
    
    vector < int > P(word.size());
    set < string > palindromes;
    
    int center = 0, rightmost = 0, low = 0, high = 0;
    for (int i = 1; i < word.length(); i++)
    {
        if (rightmost > i)
        {
            int j = center * 2 - i;
            if (P[j] < (rightmost - i))
            {
                P[i] = P[j];
                low = -1;
            }
            else
            {
                P[i] = rightmost - i;
                high = rightmost + 1;
                low = i * 2 - high;
            }
        }
        else
        {
            P[i] = 0;
            low = i - 1;
            high = i + 1;
        }

        while (low >= 0 && high < word.length() && word[low] == word[high])
        {
            P[i]++;
            low--;
            high++;
        }

        if ((i + P[i]) > rightmost)
        {
            center = i;
            rightmost = i + P[i];
        }
        
        //cout << P[i];
        
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
                                {
                                    //cout << endl;
                                    return true;
                                }

                        palindromes.insert(palindrome);
                    }
                }
        }
    }

    //cout << endl;
    
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
                cout << word << "\n";
    }

    return 0;
}
