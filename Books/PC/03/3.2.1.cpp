#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    // string()
    // 默认初始化方法，空字符串。
    string s0;
    // s0 = ""
    
    // string(const char* s)
    // 使用字符串常量或字符数组进行初始化。
    string s1("the quick brown fox jumps over the lazy dog.");
    // s1 = "the quick brown fox jumps over the lazy dog."

    // string(const string& str)
    // 使用另外一个string类实例来初始化。
    string s2(s1);
    // s2 = "the quick brown fox jumps over the lazy dog."

    // string(const string& str, size_t pos, size_t len = npos)
    // 使用另外一个string类实例，从指定位置pos开始，取len个字符，第三个
    // 参数可以省略，若省略第三个参数，则从指定位置pos开始取到字符串末尾。
    string s3(s1, 4, 5);
    string s4(s1, 10);
    // s3 = "quick"
    // s4 = "brown fox jumps over the lazy dog."

    // string(const char* s, size_t n)
    // 从字符串常量或者字符数组的指定位置开始取字符进行初始化。
    string s5("the quick brown dog jumps over the lazy fox.", 9);
    char sample[64] = "the quick brown dog jumps over the lazy fox.";
    string s6(sample, 9);
    // s5 = "the quick"
    // s6 = "the quick"

    // string (size_t n, char c)
    // 以指定数目的特定字符来填充字符串，数值35是字符#的ASCII码值。
    string s7(10, 'A');
    string s8(10, 35);
    // s7 = "AAAAAAAAAA"
    // s8 = "##########"
    
    // template <class InputIterator>
    // string(InputIterator first, InputIterator lsst)
    // 使用迭代器来指定string类实例的特定范围来进行新string类的初始化。
    string s9(s1.begin(), s1.begin() + 9);
    // s9 = "the quick"

    cout << "s1 = " << s1 << '\n';
    cout << "s2 = " << s2 << '\n';
    cout << "s3 = " << s3 << '\n';
    cout << "s4 = " << s4 << '\n';
    cout << "s5 = " << s5 << '\n';
    cout << "s6 = " << s6 << '\n';
    cout << "s7 = " << s7 << '\n';
    cout << "s8 = " << s8 << '\n';
    cout << "s9 = " << s9 << '\n';
    
    return 0;
}
