#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

const int MAXN = 1000000, TIMES = 100;

int main(int argc, char *argv[])
{
    int number[10];
    for (int i = 0; i < 10; i++)
    {
        number[i] = i + 1;
        cout << setw(3) << right << number[i];
    }
    cout << endl;

    fill(number + 5, number + 10, 5);
    for (int i = 0; i < 10; i++)
        cout << setw(3) << right << number[i];
    cout << endl;

    int test[MAXN];

    time_t begin, end;

    begin = clock();
    for (int i = 1; i <= TIMES; i++)
        for (int i = 0; i < MAXN; i++)
            test[i] = 0;
    end = clock();
    cout << "for: average time cost is " << (end - begin) / TIMES << " ms." << endl;
    
    begin = clock();
    for (int i = 1; i <= TIMES; i++)
        fill(test, test + MAXN, 0);
    end = clock();
    cout << "fill: average time cost is " << (end - begin) / TIMES << " ms." << endl;

    begin = clock();
    for (int i = 1; i <= TIMES; i++)
        memset(test, 0, sizeof(test));
    end = clock();
    cout << "memset: average time cost is " << (end - begin) / TIMES << " ms." << endl;

    return 0;
}
