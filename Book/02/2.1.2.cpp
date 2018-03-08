#include <iostream>

using namespace std;

int n, k;

int findLast()
{
    int last = 0;
    for (int i = 2; i <= n; i++)
        last = (last + k) % i;
    return (last + 1);
}

int main(int argc, char *argv[])
{
    while (cin >> n >> k, n && k)
        cout << findLast() << endl;

    return 0;
}
