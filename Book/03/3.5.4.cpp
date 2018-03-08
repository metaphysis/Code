#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int number[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    reverse(number, number + 10);

    string line = "0123456789";
    reverse(line.begin(), line.end());
    
    return 0;
}
