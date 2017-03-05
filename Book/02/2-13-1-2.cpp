#include <iostream>
#include <cstring>

using namespace std;

struct Tag
{
    int age;
    bool gender;
    char name[20];
};

int main(int argc, char *argv[])
{
    int data[10];
    for (int i = 0; i < 10; i++)
    {
        data[i] = i + 1;
        cout << data[i] << " ";
    }
    cout << endl;

    memset(data + 1, 0, sizeof(int) * 5);
    for (int i = 0; i < 10; i++) cout << data[i] << " ";
    cout << endl;

    Tag tag = (Tag){1, true, "the brown fox"};
    cout << tag.age << " " << tag.gender << " " << tag.name << endl;

    memset(&tag, 0, sizeof(tag));
    cout << tag.age << " " << tag.gender << " " << tag.name << endl;

    return 0;
}
