#include <bits/stdc++.h>

using namespace std;

struct Tag {
    int age;
    bool gender;
    char name[20];
};

int main() {
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i + 1;
        cout << data[i] << " ";
    }
    cout << endl;

    memset(data + 1, 0, sizeof(int) * 5);
    for (int i = 0; i < 10; i++) cout << data[i] << " ";
    cout << endl;

    Tag t = (Tag){1, true, "the brown fox"};
    cout << t.age << " " << t.gender << " " << t.name << endl;

    memset(&t, 0, sizeof(t));
    cout << t.age << " " << t.gender << " " << t.name << endl;

    return 0;
}
