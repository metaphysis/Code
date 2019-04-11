#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    string sentence = "the quick brown fox jumps over the lazy dog.";
    
    for (int i = 0; i < sentence.length(); i++)
        cout << sentence[i];
    cout << endl;
    
    for (string::iterator it = sentence.begin(); it != sentence.end(); it++)
        cout << *it;
    cout << endl;
    
    return 0;
}
