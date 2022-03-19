#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    char s1[] = "the quick brown fox jumps over the lazy dog.";
    string s2(s1), s3;
    
    cout << s1 << '\n';
    cout << s2 << '\n';
    cout << s3 << '\n';
    
    s3.assign(s2);
    cout << s3 << '\n';
    // s3 = "the quick brown fox jumps over the lazy dog."
    
    s3.assign(s2, 10, 5);
    cout << s3 << '\n';
    // s3 = "brown"
    
    s3.assign(s1);
    cout << s3 << '\n';
    // s3 = "the quick brown fox jumps over the lazy dog."
    
    s3.assign(s1, 9);
    cout << s3 << '\n';
    // s3 = "the quick"
    
    s3.assign(10, 'A');
    cout << s3 << '\n';
    // s3 = "AAAAAAAAAA"
    
    s3.assign(s2.begin(), s2.begin() + 9);
    cout << s3 << '\n';
    // s3 = "the quick"
    
    return 0;
}
