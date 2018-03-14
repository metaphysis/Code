// English-Number Translator
// UVa ID: 486
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<string, int> value = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, 
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, 
    {"ten", 10}, {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14}, 
    {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19}, 
    {"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50}, {"sixty", 60}, 
    {"seventy", 70}, {"eighty", 80}, {"ninety", 90}, {"hundred", 100}, {"thousand", 1000},
    {"million", 1000000}
};

int stringToInt(vector<string> number)
{
    if (number.size() == 0)
        return 0;
        
    if (number.size() == 1)
        return value[number.front()];
    
    int sign = 1;
    if (number.front() == "negative")
    {
        number.erase(number.begin());
        sign = -1;
    }

    vector<string> tag{"million", "thousand", "hundred"};
    
    int sum = 0;
    bool found = false;
    for (int i = 0; i < 3; i++)
    {
        auto index = find(number.begin(), number.end(), tag[i]);
        if (index != number.end())
        {
            vector<string> next(number.begin(), index);
            sum += stringToInt(next) * value[tag[i]];
            number.erase(number.begin(), index + 1);
            sum += stringToInt(number);
            found = true;
            break;
        }
    }
    
    if (found == false)
    {
        if (number.size() == 1)
            sum = value[number.front()];
        if (number.size() == 2)
            sum = value[number.front()] + value[number.back()];
    }

    return sign * sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line, digit;
    istringstream iss;
    
    while (getline(cin, line))
    {
        vector<string> number;
        iss.clear(); iss.str(line);
        while (iss >> digit)
            number.push_back(digit);
        cout << stringToInt(number) << '\n';  
    }
    
	return 0;
}
