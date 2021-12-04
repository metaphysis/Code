#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    // 声明一个大小为10的vector，初始值全为0。
    vector<int> numbers(10, 0);
    
    // 将第一个至第五个元素顺序赋值为1，2，3，4，5。
    iota(numbers.begin(), numbers.begin() + 5, 1);
    
    for (auto number : numbers)
        cout << setw(2) << right << number;
    cout << '\n';

    // 1 2 3 4 5 0 0 0 0 0
    
    return 0;
}
