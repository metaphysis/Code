#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    string line, word;
    line = "The quick brown fox jumps over a lazy dog";
    
    // 将输入以空格作为分隔符拆分成单词。
    istringstream iss(line);
    while (iss >> word) cout << word << "-";
    cout << endl;
    
    // 如果需要连续使用istringstream对象，注意将输入状态标志重置，否则会发生错误。
    // 读者可以尝试将iss.clear()注释掉后观察相应的输出。
    iss.clear();
    line.assign("The quick black dog jumps over a lazy fox");
    iss.str(line);
    while (iss >> word) cout << word << "-";
    cout << endl;
        
    return 0;
}
