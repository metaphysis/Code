#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string s0;
    string s1 = "the quick brown fox jumps over the lazy dog.";
    
    cout << s0 << endl;
    // ""
    
    s0.assign(s1);
    cout << s0 << endl;
    // "the quick brown fox jumps over the lazy dog."
    
    s0.assign(s1, 10, 5);
    cout << s0 << endl;
    // "brown"
    
    s0.assign(s1.begin(), s1.begin() + 9);
    cout << s0 << endl;
    // "the quick"
    
    return 0;
}
