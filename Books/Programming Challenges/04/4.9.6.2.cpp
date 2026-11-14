#include <bits/stdc++.h>

using namespace std;

struct record {
    int index, value;

    bool operator < (const record &x) const
    {
        if (value == x.value) return index < x.index;
        else return value < x.value;
    }
};

bool cmp(record x, record y)
{
    if (x.value == y.value) return x.index > y.index;
    else return x.value > y.value;
}

int main(int argc, char *argv[])
{
    vector<record> records;

    for (int i = 1; i <= 10; i++) records.push_back((record){i, i});

    // 使用重载的小于运算符进行比较。
    sort(records.begin(), records.end());

    // 使用自定义的比较函数进行比较。
    sort(records.begin(), records.end(), cmp);

    return 0;
}

