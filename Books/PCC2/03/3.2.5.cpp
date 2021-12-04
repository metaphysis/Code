#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "The quick brown fox jumps over a lazy dog";
    size_t pos1 = s.rfind("fox"), pos2 = s.find_last_of("fox");
    cout << "pos1 = " << pos1 << " pos2 = " << pos2 << '\n';
    return 0;
}
