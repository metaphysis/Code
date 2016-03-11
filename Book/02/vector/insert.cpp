#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
    vector < int > circle;
    
    for (int i = 1; i <= 10; i++)
        circle.push_back(i);
    
    for (vector<int>::iterator it = circle.begin(); it != circle.end(); it++)
        cout << *it << " ";
    cout << endl;
    
    circle.insert(circle.begin(), 100);
    circle.insert(circle.begin(), 3, 10);
    circle.insert(circle.begin(), circle.begin(), circle.begin() + 10);
    
    for (vector<int>::iterator it = circle.begin(); it != circle.end(); it++)
        cout << *it << " ";
    cout << endl;
    
    return 0;
}
