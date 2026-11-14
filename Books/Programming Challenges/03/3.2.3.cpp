#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    string s = "the quick brown fox jumps over the lazy dog.";
    
    for (int i = 0; i < s.length(); i++)
        cout << s[i];
    cout << endl;
    
    for (string::iterator it = s.begin(); it != s.end(); it++)
        cout << *it;
    cout << endl;
    
    return 0;
}
