// The Errant Physicist
// UVa ID: 126
// Verdict: Accepted
// Submission Date: 2015-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 201

int coefficients[MAXN][MAXN];
int part1[4], part2[4];

void getItem(vector<string>& c, string line)
{
    if (line[0] != '-' || line[0] != '+')
        line = '+' + line;
    
    while (true)
    {
        int plusIndex = line.rfind('+');
        int minusIndex = line.rfind('-');
        
        if (plusIndex >= 0 || minusIndex >= 0)
        {
            c.push_back(line.substr(max(plusIndex, minusIndex)));
            line = line.substr(0, max(plusIndex, minusIndex));
        }
        else
            break;
    }
}

int getExponent(string& item, char next)
{
    int exponent = 0;
    item = item.substr(1);
    while (item.length() && item[0] != next)
    {
        exponent = exponent * 10 + item[0] - '0';
        item = item.substr(1);
    }
    return exponent == 0 ? 1 : exponent;
}

void getPart(string item, int part[])
{
    // 解析符号。
    part[0] = item[0] == '-' ? -1 : 1;
    
    if (item[0] == '+' || item[0] == '-')
        item = item.substr(1);

    // 获取系数。
    int coefficient = 0;
    while (item.length() && item[0] >= '0' && item[0] <= '9')
    {
        coefficient = coefficient * 10 + item[0] - '0';
        item = item.substr(1);
    }
    part[1] = coefficient == 0 && item.length() ? 1 : coefficient;
    
    // 获取指数。
    if (item.length())
    {
        char start = item[0];
        int exponent1, exponent2;
        if (start == 'x' || start == 'y')
        {
            char next = (start == 'x' ? 'y' : 'x');
            exponent1 = getExponent(item, next);
                
            if (item.length())
                exponent2 = getExponent(item, next);
        }
        
        part[2] = start == 'x' ? exponent1 : exponent2;
        part[3] = start == 'x' ? exponent2 : exponent1;
    }
}

// 将两个项目相乘。
void multiply(string term1, string term2)
{
    memset(part1, 0, sizeof(part1));
    memset(part2, 0, sizeof(part2));
    
    getPart(term1, part1);
    getPart(term2, part2);
    
    coefficients[part1[2] + part2[2]][part1[3] + part2[3]] +=
        part1[0] * part1[1] * part2[0] * part2[1];
}

string space(int n)
{
    stringstream ss;
    string line;
    ss << n;
    ss >> line;
    return string(line.length(), ' ');
}

void output(bool printExponent, int n)
{
    if (printExponent)
        cout << n;
    else
        cout << space(n); 
}

void print(bool printExponent)
{
    bool firstItemPrinted = false;
    for (int i = 200; i >= 0; i--)
        for (int j = 0; j <= 200; j++)
            if (coefficients[i][j] != 0)
            {
                if (firstItemPrinted == false)
                {
                    if (coefficients[i][j] < 0)
                        cout << (printExponent ? " " : "-");
                    firstItemPrinted = true;
                }
                else
                {
                    cout << " ";
                    cout << (printExponent ? " " : ((coefficients[i][j] > 0) ? "+" : "-"));
                    cout << " ";
                }

                if (fabs(coefficients[i][j]) > 1)
                    output(!printExponent, fabs(coefficients[i][j]));
                else if (i == 0 && j == 0)
                    cout << (printExponent ? " " : "1");
                    
                if (i > 0)  cout << (printExponent ? " " : "x");
                if (i > 1)  output(printExponent, i);
                if (j > 0)  cout << (printExponent ? " " : "y");
                if (j > 1)  output(printExponent, j);
            }
    cout << endl;
}

int main(int ac, char *av[])
{
    string line;
    vector<string> polynomial1, polynomial2;
    
    while (getline(cin, line), line != "#")
    {
        polynomial1.clear();
        polynomial2.clear();
        
        getItem(polynomial1, line);
        getline(cin, line);
        getItem(polynomial2, line);
        
        memset(coefficients, 0, sizeof(coefficients));
        
        for (int i = 0; i < polynomial1.size(); i++)
            for (int j = 0; j < polynomial2.size(); j++)
                multiply(polynomial1[i], polynomial2[j]);
        
        print(true);
        print(false);
    }
    
	return 0;
}
