#include <iostream>

using namespace std;

int storage;
char previousOperand;
bool valueInStack;

void processInput(char input)
{
    if (input == '@')
    {
        if (previousOperand)
        {
            if (valueInStack)
            {
                cout << "ST $" << storage++ << endl;
            }
            cout << "L " << previousOperand << endl;
            previousOperand = 0;
            valueInStack = true;
        }
        cout << "N" << endl;
    }
    else if (input == '+')
    {
        if (previousOperand)
        {
            cout << "A " << previousOperand << endl;
            previousOperand = 0;
        }
        else
        {
            cout << "A $" << --storage << endl;
        }
    }
    else if (input == '-')
    {
        if (previousOperand)
        {
            cout << "S " << previousOperand << endl;
            previousOperand = 0;
        }
        else
        {
            cout << "N" << endl << "A $" << --storage << endl;
        }
    }
    else if (input == '*')
    {
        if (previousOperand)
        {
            cout << "M " << previousOperand << endl;
            previousOperand = 0;
        }
        else
        {
            cout << "M $" << --storage << endl;
        }
    }
    else if (input == '/')
    {
        if (previousOperand)
        {
            cout << "D " << previousOperand << endl;
            previousOperand = 0;
        }
        else
        {
            cout << "ST $" << storage++ << endl;
            cout << "L $" << storage - 2 << endl;
            cout << "D $" << --storage << endl;
            storage--;
        }
    }
    else
    {
        if (previousOperand)
        {
            if (valueInStack)
            {
                cout << "ST $" << storage++ << endl;
            }
            cout << "L " << previousOperand << endl;
            valueInStack = true;
        }
        previousOperand = input;
    }
}

int main(void)
{
    bool first = true;
    string input;

    while (cin >> input)
    {
        if (first)
            first = false;
        else
            cout << endl;

        storage = 0;
        previousOperand = 0;
        valueInStack = false;

        for (int i = 0; i < input.size(); i++)
            processInput(input[i]);
        processInput(0);
    }

    return 0;
}
