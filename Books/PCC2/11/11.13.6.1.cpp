#include <bits/stdc++.h>

using namespace std;

pair<int, int> findLongestPalindrome(string text)
{
    int startIndex = 0, maxLength = 0, currentLength, left, right;
    for (int i = 0, length = text.length(); i < length; i++)
    {
        currentLength = 1, left = i - 1, right = i + 1;
        while (left >= 0 && right < length && text[left] == text[right])
            left--, right++, currentLength++;

        if (currentLength > maxLength)
        {
            startIndex = i - currentLength + 1;
            maxLength = 2 * currentLength - 1;
        }

        if (i > 0 && text[i] == text[i - 1])
        {
            currentLength = 1, left = i - 2, right = i + 1;
            while (left >= 0 && right < length && text[left] == text[right])
                left--, right++, currentLength++;

            if (currentLength > maxLength)
            {
                startIndex = i - currentLength;
                maxLength = 2 * currentLength;
            }
        }
    }

    return make_pair(startIndex, maxLength);
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        pair<int, int> result = findLongestPalindrome(line);
        cout << line.substr(result.first, result.second) << endl;
    }
        
    return 0;
}
