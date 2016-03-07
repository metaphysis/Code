#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
    string sample[10];
    for (int i = 0; i < 10; i++)
    {
        sample[i] = "A";
        cout << sample[i] << " ";
    }
    cout << endl;
    
    fill(sample + 5, sample + 10, "B");
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    return 0;
}

