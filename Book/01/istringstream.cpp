#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    string line, word;
    line = "The quick brown fox jumps over a lazy dog.";
    
    istringstream iss(line);
    while (iss >> word)
        cout << word << "-";
    cout << endl;
    
    iss.clear();
    line.assign("The quick black dog jumps over a lazy fox.");
    iss.str(line);
    while (iss >> word)
        cout << word << "-";
    cout << endl;
        
    return 0;
}
