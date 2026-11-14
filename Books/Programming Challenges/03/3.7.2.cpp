#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string something = "abc";

    cout << something << endl;
    while (next_permutation(something.begin(), something.end()))
        cout << something << endl;

    cout << endl;
    cout << "after next_permutation: " << something << endl;
    cout << endl;

    something.assign("cba");
    while (prev_permutation(something.begin(), something.end()))
        cout << something << endl;
    cout << something << endl;

    cout << endl;
    cout << "after prev_permutation: " << something << endl;

    something.assign("abcdefgh");
    while (next_permutation(something.begin(), something.begin() + 3))
        cout << something << endl;
    
    return 0;
}
