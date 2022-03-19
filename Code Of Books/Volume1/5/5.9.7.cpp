#include <bits/stdc++.h>

using namespace std;

struct node
{
    int index, value;
};

bool operator<(node a, node b)
{
    return a.value < b.value;
}

int main(int argc, char *argv[])
{
    vector<node> nodes;
    for (int i = 0; i < 10; i++)
    {
        nodes.push_back((node){i, i % 2 == 0 ? 5 : i});
        cout << nodes[i].index << "->" << nodes[i].value << " ";
    }
    cout << endl;

    stable_sort(nodes.begin(), nodes.end());

    for (int i = 0; i < 10; i++)
        cout << nodes[i].index << "->" << nodes[i].value << " ";
    cout << endl;

    return 0;
}
