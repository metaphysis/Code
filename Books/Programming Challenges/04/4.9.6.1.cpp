#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int sample[10] = { 97, 3, 7, 13, 51, 23, 29, 17, 11, 83 };

    for (int i = 0; i < 10; i++) cout << sample[i] << " ";
    cout << endl;

    // 默认较小的数排序在前。
    sort(sample, sample + 10);
    for (int i = 0; i < 10; i++) cout << sample[i] << " ";
    cout << endl;

    // 使用模板函数greater<int>()指定大小关系，较大的数排序在前。
    sort(sample, sample + 10, greater<int>());
    for (int i = 0; i < 10; i++) cout << sample[i] << " ";
    cout << endl;

    return 0;
}

