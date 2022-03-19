#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> circle;
    
    for (int i = 1; i <= 10; i++)
        circle.push_back(i);
        
    for (int i = circle.size() - 1; i >= 0; i--)
        cout << setw(2) << circle[i] << " ";
    cout << endl;
    
    for (auto it = circle.begin(); it != circle.end(); it++)
        cout << setw(2) << *it << " ";
    cout << endl;
    
    return 0;
}
