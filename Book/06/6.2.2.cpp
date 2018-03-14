#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "ABCDE";
    
    int indexer = 1;
    do {
        if (indexer == 83) {
            cout << s << '\n';
            break;
        }
        indexer++;
    } while (next_permutation(s.begin(), s.end()));
    
    return 0;
}
