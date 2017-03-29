#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void manacher(string word)
{
    for (int i = word.length() - 1; i >= 0; i--)
        word.insert(word.begin() + i, '#');
    word.push_back('#');
    
    vector<int> P(word.size());
    
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
    }
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
