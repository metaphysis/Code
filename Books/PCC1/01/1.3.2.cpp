#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    string line = "the quick brown fox jumps over the lazy dog.";
    
    cout << setfill('#') << setw(60) << left << line << endl;
    cout << setw(60) << right << line << endl;
    cout << setw(60) << internal << line << endl;
    
    int number = -1234567890;
    cout << setw(20) << left << number << endl;
    cout << setw(30) << internal << number << endl;
    cout << setw(30) << right << number << endl;

    return 0;
}
