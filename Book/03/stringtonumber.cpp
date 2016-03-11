#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
    string numberText = "100";
    
    int iDecNumber = stoi(numberText);
    int iOctNumber = stoi(numberText, 0, 8);
    int iHexNumber = stoi(numberText, 0, 16);
    
    cout << iDecNumber << endl;
    cout << oct << showbase << iDecNumber << endl;
    cout << hex << iHexNumber << endl;
    
    return 0;
}
