#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

bool manacher(string word)
{
    for (int i = word.length() - 1; i >= 0; i--)
        word.insert(word.begin() + i, '#');
        
    word.push_back('|');
    word.front() = '$';

    cout << word << endl;
    
    vector < int > P (word.size());
    
    cout << P[0];
    
    int rightmost = 0, center = 0;
    for (int i = 1; i < word.size(); i++)
    {
        P[i] = (rightmost > i) ? P[2 * center - i] : 1;
        
        while (word[i - P[i]] == word[i + P[i]])
            P[i]++;
        
        if (i + P[i] > rightmost)
        {
            rightmost = i + P[i] - 1;
            center = i;
        }

        cout << P[i];
    }

    cout << endl;
    
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
