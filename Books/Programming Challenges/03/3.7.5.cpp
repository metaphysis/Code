#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "ThE qUiCk BrOwN fOx JuMpS oVeR a LaZy DoG.";

    cout << s << endl;
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    cout << s << endl;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout << s << endl;

    return 0;
}
