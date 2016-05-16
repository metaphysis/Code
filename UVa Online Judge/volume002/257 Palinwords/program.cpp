// Palinwords
// UVa IDs: 257
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

bool isPalinword(string word)
{
    string newWord;
    for (int i = 0; i < word.length(); i++)
    {
        newWord += "#";
        newWord += word[i];
    }
    newWord += "#";

    vector < int > P(newWord.size());

    //P[0] = 1;

    //int mx = 0, id;
    //for (int i = 1; i < newWord.size(); i++)
    //{
    //if (mx > i)
    //mx = min(P[2 * id - 1], mx - i);
    //else
    //P[i] = 1;

    //while (newWord[i - P[i]] == newWord[i + P[i]])
    //P[i]++;

    //if (i + P[i] > mx)
    //{
    //mx = i + P[i];
    //id = i;
    //}
    //}

    set < string > palindromes;
    
    int c = 0, r = 0;           // Here the first element in newWord has been processed.
    int m = 0, n = 0;           // The walking indices to compare if two elements are the same
    for (int i = 1; i < newWord.length(); i++)
    {
        if (i > r)
        {
            P[i] = 0;
            m = i - 1;
            n = i + 1;
        }
        else
        {
            int i2 = c * 2 - i;
            if (P[i2] < (r - i))
            {
                P[i] = P[i2];
                m = -1;         // This signals bypassing the while loop below. 
            }
            else
            {
                P[i] = r - i;
                n = r + 1;
                m = i * 2 - n;
            }
        }
        
        while (m >= 0 && n < newWord.length() && newWord[m] == newWord[n])
        {
            P[i]++;
            m--;
            n++;
        }
        
        if ((i + P[i]) > r)
        {
            c = i;
            r = i + P[i];
        }
        
        if (P[i] >= 3)
        {
            string palindrome;
            if (isalpha(newWord[i]))
                palindrome += newWord[i];

            for (int j = i + 1; j <= (i + P[i] - 1); j++)
            {
                if (isalpha(newWord[j]))
                {
                    palindrome += newWord[j];
                    palindrome.insert(palindrome.begin(), newWord[j]);
                    
                    if (palindrome.length() >= 5)
                        break;
                        
                    if (palindrome.length() >= 3)
                    {
                        if (palindromes.count(palindrome) > 0)
                            continue;
                            
                        for (auto it = palindromes.begin(); it != palindromes.end(); it++)
                        {
                            if (palindrome.find(*it) == palindrome.npos &&
                                (*it).find(palindrome) == palindrome.npos)
                                return true; 
                        }
                        
                        palindromes.insert(palindrome);
                    }
                }
            }
        }
    }

    return false;
}

void findPalinwords(string line)
{
    istringstream iss(line);
    string word;
    while (iss >> word)
    {
        if (isPalinword(word))
            cout << word << "\n";
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
            continue;

        findPalinwords(line);
    }

    return 0;
}
