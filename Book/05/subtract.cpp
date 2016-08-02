#include <iostream>
#include <algorithm>

using namespace std;

const int BASE = 10;

string subtract(string number1, string number2)
{
    int sign = 1;

    bool is_bigger = true;
    if (number1.length() < number2.length())
        is_bigger = false;
    else if (number1.length() == number2.length())
    {
        for (int i = 0; i < number1.length(); i++)
            if (number1[i] < number2[i])
            {
                is_bigger = false;
                break;
            }
    }
    if (is_bigger == false)
    {
        sign = -1;
        number1.swap(number2);
        number1.insert(number1.begin(), '0');
    }

    int borrow = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int diff = number1[i] - '0' - (j >= 0 ? (number2[j] - '0') : 0) - borrow;
        if (diff < 0)
        {
            diff += BASE;
            borrow = 1;
        }
        number1[i] = diff + '0';
    }

    while (number1.front() == '0' && number1.length() > 1)
        number1.erase(number1.begin());

    if (sign == -1)
        number1.insert(number1.begin(), '-');

    return number1;
}

int main(int argc, char *argv[])
{
    string number1, number2;

    while (cin >> number1 >> number2)
        cout << subtract(number1, number2) << endl;

    return 0;
}
