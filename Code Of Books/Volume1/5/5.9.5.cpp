#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line = "987654321";
    
    cout << line << endl;
    partial_sort(line.begin(), line.begin() + 5, line.end());
    cout << line << endl;
    
    return 0;
}
