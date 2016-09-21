#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // 需要在进行任何输入输出前使用。
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL); ios_base.sync_with_stdio(false);

    // 后续不能将scanf，printf与cin，cout混用。输出换行符时，避免使用endl，否则
    // 每次输出时均会刷新缓冲区，增加时间消耗。

    // 后续代码...

    return 0;
}
