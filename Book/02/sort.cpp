#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}

int main(int argc, char * argv[])
{
    int sample[10] = { 97, 3, 7, 13, 51, 23, 29, 17, 11, 83 };
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    sort(sample, sample + 10);
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    sort(sample, sample + 10, cmp);
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    return 0;
}

