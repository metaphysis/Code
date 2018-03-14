// Spreadsheet Calculator
// UVa ID: 215
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cell[20][10];
bool calculated[20][10];
string original[20][10];
string expression[20][10];
int rows, columns;
set <string> undefined;

string trim(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);
    return line;
}

string split(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (line[i] == '+')
            line[i] = ' ';
        else if (line[i] == '-')
            line.insert(line.begin() + i, ' ');
    }
    return line;
}

bool evaluate(int, int);

bool getValue(string variable, int& value)
{
    int sign = 1;
    if (variable[0] == '-')
    {
        sign = -1;
        variable.erase(variable.begin());
    }
    
    if (isalpha(variable[0]))
    {
        int ii = variable[0] - 'A';
        int jj = variable[1] - '0';
        
        if (calculated[ii][jj])
        {
            value = sign * cell[ii][jj];
            return true;
        }
        else
        {
            if (undefined.count(variable) > 0)
                return false;
                
            undefined.insert(variable);
            if (evaluate(ii, jj))
            {
                undefined.erase(variable);
                calculated[ii][jj] = true;
                value = sign * cell[ii][jj];
                return true;
            }
            
            return false;
        }
    }
    else
    {
        value = sign * stoi(variable);
        return true;
    }
}

bool evaluate(int i, int j)
{
    string variable;
    vector <string> variables;
    istringstream iss(expression[i][j]);
    while (iss >> variable)
        variables.push_back(variable);

    int sum = 0;
    for (int i = 0; i < variables.size(); i++)
    {
        int value;
        if (getValue(variables[i], value))
            sum += value;
        else
            return false;
    }

    cell[i][j] = sum;
    calculated[i][j] = true;

    return true;
}

void calculate()
{
    int cellCalculated = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            undefined.clear();
            if (calculated[i][j] || evaluate(i, j))
                cellCalculated++;
        }

    if (cellCalculated == rows * columns)
    {
        cout << " ";
        for (int i = 0; i < columns; i++)
            cout << setw(6) << right << i;
        cout << endl;
        
        for (int i = 0; i < rows; i++)
        {
            cout << (char)('A' + i);
            for (int j = 0; j < columns; j++)
                cout << setw(6) << right << cell[i][j];
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                if (calculated[i][j] == false)
                    cout << (char)('A' + i) << j << ": " << original[i][j] << endl;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    string line;
    while (cin >> rows >> columns, rows && columns)
    {
        cin.ignore();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
            {
                getline(cin, line);
                original[i][j] = trim(line);
                expression[i][j] = split(original[i][j]);
                calculated[i][j] = false;
                cell[i][j] = 0;
            }

        calculate();
        cout << endl;
    }
    
	return 0;
}
