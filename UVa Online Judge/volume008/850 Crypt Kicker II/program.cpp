// Crypt Kicker II （解密 II）
// PC/UVa IDs: 110304/850, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2016-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> encrypted;
vector<string> plain;

void printPlain(string cipher)
{
    for (int m = 0; m < encrypted.size(); m++)
    {
        for (int n = 0; n < encrypted[m].size(); n++)
        {
            string tmp = encrypted[m][n];
            for (int j = 0; j < tmp.length(); j++)
                cout << cipher[tmp[j] - 'a'];
            if (n < encrypted[m].size() - 1)
                cout << " ";
        }
        cout << endl;
    }
}

void decipher()
{
    bool allMatched = true;
    for (int i = 0; i < encrypted.size(); i++)
    {
        if (encrypted[i].size() != plain.size())
            continue;

        allMatched = true;
        for (int j = 0; j < plain.size(); j++)
            if (encrypted[i][j].length() != plain[j].length())
            {
                allMatched = false;
                break;
            }
        if (allMatched == false)
            continue;

        string cipher(26, '*');
        for (int k = 0; k < plain.size(); k++)
        {
            string e = encrypted[i][k];
            string p = plain[k];

            for (int m = 0; m < e.length(); m++)
            {
                if (cipher[e[m] - 'a'] == '*')
                    cipher[e[m] - 'a'] = p[m];
                else if (cipher[e[m] - 'a'] != p[m])
                {
                        allMatched = false;
                        break;
                }
            }
            
            if (allMatched == false)
                break;
        }

        if (allMatched == true)
        {
            printPlain(cipher);
            break;
        }
    }

    if (allMatched == false)
        cout << "No solution." << endl;
}

int main(int ac, char *av[])
{
    string word, line;
    int cases;

    istringstream iss("the quick brown fox jumps over the lazy dog");
    while (iss >> word)
        plain.push_back(word);

    cin >> cases;
    cin.ignore();
    getline(cin, line);
    while (cases--)
    {
        encrypted.clear();
        while (getline(cin, line), line.length() > 0)
        {
            iss.clear();
            iss.str(line);
            vector<string> tmp;
            while (iss >> word) tmp.push_back(word);
            encrypted.push_back(tmp);
        }

        decipher();

        if (cases > 0) cout << endl;
    }

    return 0;
}
