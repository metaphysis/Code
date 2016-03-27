// Code Breaking
// UVa IDs: 179
// Verdict: Accepted
// Submission Date: 2016-03-27
// UVa Run Time: 0.026s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string plaintext, cyphertext1, cyphertext2;
vector < int >k, key;

string encrypt(string plain)
{
    string encrypted(plain);
    for (int i = 0; i < key.size(); i++)
        encrypted[key[i] - 1] = plain[i];
    return encrypted;
}

void decrypt(string encrypted)
{
    int index = 0;
    int keyLength = key.size();
    int textLength = encrypted.length();

    while (index < textLength)
    {
        int subLength = min(keyLength, textLength - index);
        string subEncrypted = encrypted.substr(index, subLength);
        while (subEncrypted.length() < keyLength)
            subEncrypted += '?';
        for (int i = 0; i < keyLength; i++)
            cout << subEncrypted[key[i] - 1];
        index += keyLength;
    }
}

bool verifyKey()
{
    int index = 0;
    int keyLength = key.size();
    int textLength = plaintext.length();

    while (index < textLength)
    {
        int subLength = min(keyLength, textLength - index);
        string subPlain = plaintext.substr(index, subLength);
        string subEncrypted = cyphertext1.substr(index, subLength);
        while (subPlain.length() < keyLength)
            subPlain += '?';
        while (subEncrypted.length() < keyLength)
            subEncrypted += '?';
        if (encrypt(subPlain) != subEncrypted)
            return false;
        index += keyLength;
    }

    return true;
}

void initializeKey(int keyLength)
{
    key.clear();
    for (int i = 1; i <= keyLength; i++)
        key.push_back(i);
}

bool findPermutation(int keyLength)
{
    initializeKey(keyLength);

    do
    {
        if (verifyKey())
            return true;
    }
    while (next_permutation(key.begin(), key.end()));

    return false;
}

// backtrack
int maxTimesTry = 10000;
int timesTried = 0;
bool keyFound = false, finish = false;
string source, target;
vector < bool > matched;

void backtrack(int index, int keyLength)
{
    if (index == keyLength)
    {
        if (verifyKey())
        {
            keyFound = true;
            finish = true;
        }

        if (timesTried++ > maxTimesTry)
            finish = true;

        return;
    }

    for (int i = 0; i < target.length(); i++)
        if (matched[i] == false && source[index] == target[i])
        {
            matched[i] = true;
            key[index] = i + 1;
            backtrack(index + 1, keyLength);
            if (finish)
                return;
            matched[i] = false;
        }
}

bool findKeyByBacktrack(int keyLength)
{
    int index = 0;
    while (index < plaintext.length())
    {
        initializeKey(keyLength);
        finish = false;
        timesTried = 0;
        keyFound = false;
        source = plaintext.substr(index, keyLength);
        target = cyphertext1.substr(index, keyLength);
        if (source.length() < keyLength)
            break;

        matched.clear();
        for (int i = 1; i <= keyLength; i++)
            matched.push_back(false);

        backtrack(0, keyLength);

        if (keyFound)
            break;
        index += keyLength;
    }

    return keyFound;
}

bool findKey()
{
    int keyIndex = 0;
    while (keyIndex < k.size())
    {
        if (k[keyIndex] <= 7 && findPermutation(k[keyIndex]))
            return true;

        if (findKeyByBacktrack(k[keyIndex]))
            return true;

        keyIndex++;
    }

    return false;
}

bool findK()
{
    k.clear();

    int keyLength = 1, textLength = plaintext.length();
    while (keyLength <= textLength)
    {
        int index = 0;
        bool keyLengthMatched = true;
        while (index < textLength)
        {
            int subLength = min(keyLength, textLength - index);

            string subText1 = plaintext.substr(index, subLength);
            string subText2 = cyphertext1.substr(index, subLength);

            sort(subText1.begin(), subText1.end());
            sort(subText2.begin(), subText2.end());

            if (subText1 != subText2)
            {
                keyLengthMatched = false;
                break;
            }

            index += keyLength;
        }

        if (keyLengthMatched)
            k.push_back(keyLength);

        keyLength++;
    }

    return k.size() > 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    while (getline(cin, plaintext), plaintext != "#")
    {
        getline(cin, cyphertext1);
        getline(cin, cyphertext2);

        if (findK() && findKey())
            decrypt(cyphertext2);
        else
            cout << cyphertext2;
        cout << "\n";
    }

    return 0;
}
