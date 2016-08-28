#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int numerator, denominator;

    while (cin >> numerator >> denominator, denominator > 0)
    {
        vector < int > digits(denominator + 1), position(denominator + 1);
        vector < bool > appeared(denominator + 1);

        fill(appeared.begin(), appeared.end(), false);

        int index = 0;
        while (appeared[numerator] == false && numerator > 0)
        {
            appeared[numerator] = true;
            digits[index] = 10 * numerator / denominator;
            position[numerator] = index;
            
            index++;
            numerator = 10 * numerator % denominator;
        }
    }
    
    return 0;
}
