#include <iostream>
#include <algorithm>

using namespace std;

const int BASE = 10;

string add(string number1, string number2)
{
    if (number1.length() < number2.length())
        number1.swap(number2);
    number1.insert(number1.begin(), '0');

    int carry = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int sum = number1[i] - '0' + (j >= 0 ? (number2[j] - '0') : 0) + carry;
        number1[i] = sum % BASE + '0';
        carry = sum / BASE;
    }

    while (number1.front() == '0' && number1.length() > 1)
        number1.erase(number1.begin());

    return number1;
}

int main(int argc, char *argv[])
{
    string number1, number2;

    while (cin >> number1 >> number2)
        cout << add(number1, number2) << endl;

    return 0;
}
