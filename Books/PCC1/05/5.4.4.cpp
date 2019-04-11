#include <regex>

string pattern = R"(^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$)";
regex romanExp(pattern, regex_constants::ECMAScript);

bool validateRoman(string &roman)
{
    return regex_match(roman, romanExp);
}

map<char, int> letters = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000},
};

int roman2Arab(string &roman)
{
    int arab = 0, idx = 0;
    while (idx < roman.length() - 1) {
        int previous = letters[roman[idx]], next = letters[roman[idx + 1]];
        if (previous < next) arab += next - previous, idx += 2;
        else arab += previous, idx += 1;
    }
    if (idx < roman.length()) arab += letters[roman[idx]];
    return arab;
}

vector<int> numbers = {
    3000, 2000, 1000, 900, 500, 400, 300, 200, 100,
    90, 50, 40, 30, 20, 10,
    9, 8, 7, 6, 5, 4, 3, 2, 1
};

vector<string> symbols = {
    "MMM", "MM", "M", "CM", "D", "CD", "CCC", "CC", "C",
    "XC", "L", "XL", "XXX", "XX", "X",
    "IX", "VIII", "VII", "VI", "V", "IV", "III", "II", "I"
};

string arab2Roman(int arab)
{
    string roman;
    while (arab > 0) {
        for (int i = 0; i < numbers.size(); i++)
            if (arab >= numbers[i]) {
                roman += symbols[i];
                arab -= numbers[i];
                break;
            }
    }
    return roman;
}

