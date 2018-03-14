#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<int, int> cnt = {{1, 10}};
    auto it = --cnt.end();
    cout << it->first << ' ' << it->second << endl;

    return 0;
}
