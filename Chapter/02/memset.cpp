#include <iostream>
#include <cstring>
using namespace std;

struct tag
{
    int first;
    bool second;
    char third[20];
};

int main(int argc, char *argv[])
{
    int sample[10];
    for (int i = 0; i < 10; i++)
    {
        sample[i] = i + 1;
        cout << sample[i] << " ";
    }
    cout << endl;

    memset(sample + 1, 0, 5 * sizeof(int));
    for (int i = 0; i < 10; i++)
        cout << sample[i] << " ";
    cout << endl;

    tag aTag = (tag) { 1, true, "the brown fox" };
    cout << aTag.first << " " << aTag.second << " " << aTag.third << endl;
    
    memset(&aTag, 0, sizeof(tag));
    cout << aTag.first << " " << aTag.second << " " << aTag.third << endl;
    
    return 0;
}
