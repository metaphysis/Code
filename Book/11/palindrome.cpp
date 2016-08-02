#include <iostream>

using namespace std;

pair<int, int> findLongestPalindrome(string text)
{
    int start_index = 0, max_length = 0, current_length, left, right;
    for (int i = 0, length = text.length(); i < length; i++)
    {
        current_length = 1, left = i - 1, right = i + 1;
        while (left >= 0 && right < length && text[left] == text[right])
            left--, right++, current_length++;

        if (current_length > max_length)
        {
            start_index = i - current_length + 1;
            max_length = 2 * current_length - 1;
        }

        if (i > 0 && text[i] == text[i - 1])
        {
            current_length = 1, left = i - 2, right = i + 1;
            while (left >= 0 && right < length && text[left] == text[right])
                left--, right++, current_length++;

            if (current_length > max_length)
            {
                start_index = i - current_length;
                max_length = 2 * current_length;
            }
        }
    }

    return make_pair(start_index, max_length);
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
