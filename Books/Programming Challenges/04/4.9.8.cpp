#include <bits/stdc++.h>

using namespace std;

int number[10] = { 2, 3, 5, 5, 7, 2, 2, 3, 3, 5 };

void display(string tip)
{
    cout << tip;
    for (int i = 0; i < 10; i++)
        cout << " " << number[i];
    cout << endl;
}

int main(int argc, char *argv[])
{
    display(" no operation:");
    
    unique(number, number + 10);
    display(" after unique:");
    
    sort(number, number + 10);
    display("   after sort:");
    
    int n = unique(number, number + 10) - number;
    display(" after unique:");
    
    cout << "no duplicated:";
    for (int i = 0; i < n; i++)
        cout << " " << number[i];
    cout << endl;
        
    return 0;
}
