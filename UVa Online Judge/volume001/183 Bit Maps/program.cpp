// Bit Maps
// UVa ID: 183
// Verdict: Accepted
// Submission Date: 2016-03-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string category, buffer;
int row, column;
char matrix[210][210];

// trim out the space in input line
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

// transform bit to code
string getCode(int top, int left, int bottom, int right)
{
    // is all same in area
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

    // get middle of row and column
    int middleRow = (top + bottom) / 2;
    int middleColumn = (left + right) / 2;

    vector < string > codes;
    if (left != right && top != bottom)
    {
        // quarter 1, 2, 3, 4
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(top, middleColumn + 1, middleRow, right));
        codes.push_back(getCode(middleRow + 1, left, bottom, middleColumn));
        codes.push_back(getCode(middleRow + 1, middleColumn + 1, bottom,
                                right));
    }
    else if (left == right)
    {
        // quarter 1, 3
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(middleRow + 1, left, bottom, middleColumn));
    }
    else if (top == bottom)
    {
        // quarter 1, 2
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(top, middleColumn + 1, middleRow, right));
    }

    // get code from sub area
    string bitCode;
    bool allOne = true, allZero = true;
    for (int i = 0; i < codes.size(); i++)
    {
        if (codes[i].front() == '1')
        {
            allZero = false;
            bitCode += '1';
        }
        else if (codes[i].front() == '0')
        {
            allOne = false;
            bitCode += '0';
        }
        else
        {
            allOne = false;
            allZero = false;
            bitCode += codes[i];
        }
    }

    // return result
    if (allOne)
        return "1";
    if (allZero)
        return "0";
    return "D" + bitCode;
}

// transform bit to code
void bitToCode()
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            matrix[i][j] = buffer[i * column + j];

    cout << "D" << right << setw(4)
         << row << right << setw(4) << column << "\n";

    string code = getCode(0, 0, row - 1, column - 1);

    while (code.length() > 50)
    {
        cout << code.substr(0, 50) << endl;
        code = code.substr(50);
    }
    if (code.length() > 0)
        cout << code << endl;
}

// index of current position in code
void getBit(int &index, int top, int left, int bottom, int right)
{
    if (buffer[index] != 'D')
    {
        for (int i = top; i <= bottom; i++)
            for (int j = left; j <= right; j++)
                matrix[i][j] = buffer[index];
    }
    else
    {
        int middleRow = (top + bottom) / 2;
        int middleColumn = (left + right) / 2;

        if (left != right && top != bottom)
        {
            // quarter 1, 2, 3, 4
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, top, middleColumn + 1, middleRow, right);
            getBit(++index, middleRow + 1, left, bottom, middleColumn);
            getBit(++index, middleRow + 1, middleColumn + 1, bottom, right);
        }
        else if (left == right)
        {
            // quarter 1, 3
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, middleRow + 1, left, bottom, middleColumn);
        }
        else if (top == bottom)
        {
            // quarter 1, 2
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, top, middleColumn + 1, middleRow, right);
        }
    }
}

// transform code to bit
void codeToBit()
{
    int index = 0;
    getBit(index, 0, 0, row - 1, column - 1);

    cout << "B" << right << setw(4)
         << row << right << setw(4) << column << "\n";

    string bit;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            bit += matrix[i][j];

    while (bit.length() > 50)
    {
        cout << bit.substr(0, 50) << endl;
        bit = bit.substr(50);
    }

    if (bit.length() > 0)
        cout << bit << endl;
}

// process by category of input
void process()
{
    if (category == "B")
        bitToCode();
    else
        codeToBit();
}

// read category of input, row, column
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
        else if (line != "#")
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
