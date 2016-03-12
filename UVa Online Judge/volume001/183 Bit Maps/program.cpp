// Bit Maps
// UVa IDs: 183
// Verdict:
// Submission Date:
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

string category, code, buffer;
int row, column;
char matrix[210][210];

string trim(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);
        else
            break;

    while (line.length() > 0 && isblank(line.front()))
        line.erase(line.begin());

    return line;
}

string getCode(int top, int left, int bottom, int right)
{
    for (int i = top; i <= bottom; i++)
    {
        for (int j = left; j <= right; j++)
            cout << matrix[i][j];
        cout << endl;
    }
    
    if (top == bottom)
    {
        bool allSame = true;
        for (int i = left; i < right; i++)
            if (matrix[top][i] != matrix[top][i + 1])
            {
                allSame = false;
                break;
            }
           
        if (allSame)     
            return matrix[top][left] == '1' ? "1" : "0";
    }
    else if (left == right)
    {
        bool allSame = true;
        for (int i = top; i < bottom; i++)
            if (matrix[i][left] != matrix[i + 1][left])
            {
                allSame = false;
                break;
            }
        
        if (allSame)        
            return matrix[top][left] == '1' ? "1" : "0";        
    }
    
    int middleRow = (top + bottom) / 2;
    int middleColumn = (left + right) / 2;

    
    string topLeftCode = getCode(top, left, middleRow, middleColumn);
    string topRightCode = getCode(top, middleColumn + 1, middleRow, right);
    string bottomLeftCode = getCode(middleRow + 1, left, bottom, middleColumn);
    string bottomRightCode = getCode(middleRow + 1, middleColumn + 1, bottom, right);

    string bitCode;

    if (topLeftCode.front() == '1' && topRightCode.front() == '1' &&
            bottomLeftCode.front() == '1' && bottomRightCode.front() == '1')
        bitCode += '1';
    else if (topLeftCode.front() == '0' && topRightCode.front() == '0' &&
             bottomLeftCode.front() == '0' && bottomRightCode.front() == '0')
        bitCode += '0';
    else
        bitCode += 'D';

    if (topLeftCode.front() == 'D')
        bitCode += topLeftCode;
    else
        bitCode += topLeftCode.front();

    if (topRightCode.front() == 'D')
        bitCode += topRightCode;
    else
        bitCode += topRightCode.front();

    if (bottomLeftCode.front() == 'D')
        bitCode += bottomLeftCode;
    else
        bitCode += bottomLeftCode.front();

    if (bottomRightCode.front() == 'D')
        bitCode += bottomRightCode;
    else
        bitCode += bottomRightCode.front();

    return bitCode;
}

void bitToCode()
{
    cout << category << " " << row << " " << column << endl;
    cout << buffer << endl;
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            matrix[i][j] = buffer[i * column + j];
            cout << matrix[i][j];
        }
        cout << endl;
    }

    cout << getCode(0, 0, row - 1, column - 1) << endl;
}

void getBit()
{
}

void codeToBit()
{
    cout << category << " " << row << " " << column << endl;
    cout << buffer << endl;
}

void process()
{
    if (category == "B")
        bitToCode();
    else
        codeToBit();
}

void read(string line)
{
    istringstream iss(line);
    iss >> category >> row >> column;
}

int main(int argc, char *argv[])
{
    string line;
    bool categorySetted = false;

    while (getline(cin, line))
    {
        line = trim(line);

        if (line.find(' ') != line.npos)
        {
            if (categorySetted == false)
            {
                categorySetted = true;
                read(line);
            }
            else
            {
                process();
                buffer.clear();
                read(line);
            }
        }
        else if(line != "#")
        {
            buffer += trim(line);
        }
        else if (line == "#")
        {
            process();
            break;
        }
    }

    return 0;
}
