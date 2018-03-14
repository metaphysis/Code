// Roman Numerals
// UVa ID: 185
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string leftPart, rightPart, lastPart;
string leftColumn = "IXCM", rightColumn = "VLD", allRoman = "IVXLCDM";
int numbers[] = {1, 5, 10, 50, 100, 500, 1000};
string pattern = R"(^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$)";
regex romanExp(pattern, regex_constants::ECMAScript);

bool isRoman(string &roman)
{
    return regex_match(roman, romanExp);
}

int romanToNumber(string roman)
{
    int number = 0, index = 0;
    while (index < roman.length() - 1)
    {
        int first = allRoman.find(roman[index]);
        int second = allRoman.find(roman[index + 1]);

        if (numbers[first] < numbers[second])
        {
            number += numbers[second] - numbers[first];
            index += 2;
        }
        else
        {
            number += numbers[first];
            index++;
        }
    }
    if (index < roman.length())
        number += numbers[allRoman.find(roman[index])];

    return number;
}

void parse(string &line)
{
    int plusIndex = line.find('+');
    int equalIndex = line.find('=');

    leftPart = line.substr(0, plusIndex);
    rightPart = line.substr(plusIndex + 1, equalIndex - plusIndex - 1);
    lastPart = line.substr(equalIndex + 1);
}

string Roman()
{
    if (!isRoman(leftPart) || !isRoman(rightPart) || !isRoman(lastPart))
        return "Incorrect";
    return (romanToNumber(leftPart) + romanToNumber(rightPart) ==
        romanToNumber(lastPart)) ? "Correct" : "Incorrect";
}

int times = 0;
bool finished = false;
set<string> solutions;
vector<int> digits;
vector<bool> used;
string matchNeed;

int arabicToNumber(string arabic)
{
    int number = 0;
    for (int i = 0; i < arabic.length(); i++)
        number = number * 10 + digits[matchNeed.find(arabic[i])];
    return number;
}

void backtrack(int index)
{
    if (finished)
        return;

    if (index == matchNeed.length())
    {
        int leftNumber, rightNumber, lastNumber;

        // zero will never as a leading digit
        leftNumber = digits[matchNeed.find(leftPart[0])];
        rightNumber = digits[matchNeed.find(rightPart[0])];
        lastNumber = digits[matchNeed.find(lastPart[0])];

        if (leftNumber == 0 || rightNumber == 0 || lastNumber == 0)
            return;

        leftNumber = arabicToNumber(leftPart);
        rightNumber = arabicToNumber(rightPart);
        lastNumber = arabicToNumber(lastPart);

        // zero will never appear on its own
        if (leftNumber == 0 || rightNumber == 0 || lastNumber == 0)
            return;

        if (leftNumber + rightNumber == lastNumber)
        {
            string pair;
            for (int i = 0; i < matchNeed.length(); i++)
            {
                pair += matchNeed[i];
                pair += (char)(digits[i] + '0');
            }

            if (solutions.count(pair) == 0)
            {
                solutions.insert(pair);
                times++;
            }
        }

        if (times >= 2)
        {
            finished = true;
        }

        return;
    }

    for (int i = 0; i < used.size(); i++)
        if (used[i] == false)
        {
            used[i] = true;
            digits[index] = i;
            backtrack(index + 1);
            used[i] = false;
        }
}

string Arabic(string &line)
{
    digits.clear();
    matchNeed.clear();
    for (int i = 0; i < allRoman.length(); i++)
        if (line.find(allRoman[i]) != line.npos)
        {
            matchNeed += allRoman[i];
            digits.push_back(0);
        }

    used.clear();
    for (int i = 0; i <= 9; i++) used.push_back(false);

    solutions.clear();
    finished = false;
    times = 0;
    backtrack(0);

    if (times == 0) return "impossible";
    else if (times == 1) return "valid";
    else return "ambiguous";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "#")
    {
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);
        parse(line);
        cout << Roman() << " " << Arabic(line) << "\n";
    }

    return 0;
}
