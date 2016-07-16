// Bits
// UVa ID: 293
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

string message;
int i;

int getBits();

int convertToBits(int length)
{
    if (length == 1)
        return 0;

    int bit = 1;
    for (int i = 2; i < length; i *= 2)
        bit++;
    return bit;
}

int getRecord()
{
    i++;

    int bits = 0;
    while (message[i] != '}')
    {
        while (message[i] != ':')
            i++;
        i++;
        bits += getBits();
    }

    i++;

    return bits;
}

int getArray()
{
    i += 6;

    int sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int startLength = 0;
    while (message[i] != '.')
    {
        startLength = startLength * 10 + message[i] - '0';
        i++;
    }

    startLength *= sign;

    i += 2;
    sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int endLength = 0;
    while (message[i] != ']')
    {
        endLength = endLength * 10 + message[i] - '0';
        i++;
    }

    endLength *= sign;

    i += 3;

    return (endLength - startLength + 1) * getBits();
}

int getString()
{
    i += 7;

    int length = 0;
    while (message[i] != ')')
    {
        length = length * 10 + message[i] - '0';
        i++;
    }

    i++;

    return length * 7;
}

int getEnum()
{
    i++;

    int length = 1;
    while (message[i] != ')')
    {
        if (message[i] == ',')
            length++;
        i++;
    }

    i++;
    return convertToBits(length);
}

int getRange()
{
    i++;

    int sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int startLength = 0;
    while (message[i] != '.')
    {
        startLength = startLength * 10 + message[i] - '0';
        i++;
    }
    startLength *= sign;

    i += 2;

    sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int endLength = 0;
    while (message[i] != ']')
    {
        endLength = endLength * 10 + message[i] - '0';
        i++;
    }
    endLength *= sign;

    i++;

    return convertToBits(endLength - startLength + 1);
}

int getBits()
{
    if (message[i] == '{')
        return getRecord();
    if (message[i] == 'a')
        return getArray();
    if (message[i] == 's')
        return getString();
    if (message[i] == '(')
        return getEnum();
    if (message[i] == '[')
        return getRange();
}

void process()
{
    i = 0;
    while (i < message.length())
    {
        cout << "A \"";
        while (message[i] != ':')
        {
            cout << message[i];
            i++;
        }

        i++;
        cout << "\" message requires " << getBits() << " bits." << endl;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    getline(cin, line);

    char ascii;
    while (cin >> ascii)
        message += ascii;

    process();

    return 0;
}
