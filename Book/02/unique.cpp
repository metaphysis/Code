#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return a < b;
}

int main(int argc, char * argv[])
{
    int sample[10] = { 2, 3, 5, 5, 7, 2, 2, 3, 3, 5 };
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    int m = unique(sample, sample + 10) - sample;
    for (int i = 0; i < m; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    sort(sample, sample + 10, cmp);
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    int n = unique(sample, sample + 10) - sample;
    for (int i = 0; i < n; i++)
        cout << sample[i] << " ";
    cout << endl;
    
    return 0;
}

