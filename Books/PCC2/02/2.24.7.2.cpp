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
        if (i) cout << ' ';
        cout << data[i];
    }
    cout << '\n';

    memset(data + 1, 0, sizeof(int) * 5);
    for (int i = 0; i < 10; i++) {
        if (i) cout << ' ';
        cout << data[i];
    }
    cout << '\n';

    Tag t = (Tag){1, true, "the brown fox"};
    cout << t.age << " " << t.gender << " " << t.name << '\n';

    memset(&t, 0, sizeof(t));
    cout << t.age << " " << t.gender << " " << t.name << '\n';

    return 0;
}
