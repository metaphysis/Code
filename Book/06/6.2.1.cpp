#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "ABCDE", t = "CEADB";
    
    int indexer = 1;
    do {
        if (s == t) {
            cout << indexer << '\n';
            break;
        }
        indexer++;
    } while (next_permutation(s.begin(), s.end()));
    
    return 0;
}
