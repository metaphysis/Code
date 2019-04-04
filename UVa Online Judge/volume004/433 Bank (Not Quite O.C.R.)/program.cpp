// Bank (Not Quite O.C.R.)
// UVa ID: 433
// Verdict: Accepted
// Submission Date: 2016-07-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> digits = {
    "010101111", "000001001", "010011110", "010011011", "000111001",
    "010110011", "010110111", "010001001", "010111111", "010111011"
};

vector<set<int>> garbledNumbers(10);
void backtrack(int indexer, int number)
{
    for (int i = 1, mask = 1; i <= 9; i++, mask <<= 1)
        if ((number & mask) > 0)
        {
            int next_number = number ^ mask;
            garbledNumbers[indexer].insert(next_number);
            backtrack(indexer, next_number);
        }
}

bool checksum(vector<int> &accountDigits)
{
    int sum = 0;
    for (int i = 9; i >= 1; i--)
        sum += i * accountDigits[9 - i];
    return (sum % 11) == 0;
}

void display(vector<int> answer, int countOfSolutions)
{
    if (countOfSolutions >= 2)
        cout << "ambiguous\n";
    else if (countOfSolutions == 0)
        cout << "failure\n";
    else
    {
        for (auto digit : answer)
            cout << digit;
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    map<int, int> numbers;
    for (int i = 0; i <= 9; i++)
    {
        bitset<9> converter(digits[i]);
        int value = (int)converter.to_ulong();
        numbers[value] = i;
        backtrack(i, value);
    }

    string line; getline(cin, line); int cases = stoi(line);

    for (int i = 1; i <= cases; i++)
    {
        // read the segment presentation of digit
        vector<string> account(3);
        for (int j = 0; j < 3; j++)
        {
            getline(cin, line);
            string segments;
            for (int k = 0; k < line.length() && k < 27; k++)
                segments += (line[k] == ' ' ? '0' : '1');
            while (segments.length() < 27) segments += '0';
            account[j] = segments;
        }

        // find if garbled number exist or not
        vector<int> accountDigits;

        int garbledIndex = -1, garbledValue;
        for (int j = 0; j < 9; j++)
        {
            string digitText;
            for (int k = 0; k < 3; k++) digitText += account[k].substr(j * 3, 3);

            bitset<9> binary(digitText);
            int value = (int)binary.to_ulong();

            if (numbers.find(value) != numbers.end())
                accountDigits.push_back(numbers[value]);
            else
            {
                accountDigits.push_back(-1);
                garbledIndex = j;
                garbledValue = value;
            }
        }

        // one digit is garbled
        int countOfSolutions = 0;
        vector<int> answer(accountDigits);

        if (garbledIndex != -1)
        {
            for (int j = 0; j <= 9; j++)
                if (garbledNumbers[j].find(garbledValue) != garbledNumbers[j].end())
                {
                    accountDigits[garbledIndex] = j;
                    if (checksum(accountDigits))
                    {
                        answer.assign(accountDigits.begin(), accountDigits.end());
                        countOfSolutions++;
                    }
                    if (countOfSolutions >= 2) break;
                }
                
            display(answer, countOfSolutions);
            continue;
        }

        // check the account is valid or not
        if (checksum(accountDigits))
        {
            display(answer, 1);
            continue;
        }

        // find others solutions
        vector<string> candidates = {"8", "034789", "8", "89", "89", "689", "8", "0389", "8", "8"};
        vector<int> backup(accountDigits);
        countOfSolutions = 0;

        for (int j = 0; j < 9; j++)
        {
            for (auto ascii : candidates[backup[j]])
            {
                accountDigits[j] = ascii - '0';
                if (checksum(accountDigits))
                {
                    answer.assign(accountDigits.begin(), accountDigits.end());
                    countOfSolutions++;
                }

                if (countOfSolutions >= 2)
                    goto skip;
            }
            accountDigits.assign(backup.begin(), backup.end());
        }

        skip:
        display(answer, countOfSolutions);
    }

    return 0;
}
