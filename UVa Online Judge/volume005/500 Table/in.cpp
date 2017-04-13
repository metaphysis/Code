#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const char separator = (char)(179), right_line_separator = (char)(180),
    top_right_corner = (char)(191), bottom_left_corner = (char)(192),
    bottom_line_separator = (char)(193), top_line_separator = (char)(194),
    left_line_separator = (char)(195), link = (char)(196),
    middle_line_separator = (char)(197), bottom_right_corner = (char)(217),
    top_left_corner = (char)(218);
    
int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    // number of datasets
    int cases = rand() % 10 + 1;
    cout << cases << '\n';
    
    // generate every dataset
    for (int c = 1; c <= cases; c++)
    {
        cout << '\n';
        
        // lines and columns of table
        int lines = rand() % 98 + 3;
        int columns = rand() % 10 + 1;
        
        int length_of_cell[columns];
        for (int i = 0; i < columns; i++)
            length_of_cell[i] = rand() % 10 + 6;

        cout << top_left_corner;
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < length_of_cell[i] + 2; j++)
                cout << link;
            cout << top_line_separator;
        }
        cout << top_right_corner << '\n';
        
        string content = "ABCDEFG HIJKLMN OPQRST UVWXYZ";
        for (int i = 1; i <= lines / 2; i++)
        {
            if (i > 1)
            {
                cout << left_line_separator;
                for (int j = 0; j < columns; j++)
                {
                    for (int k = 0; k < length_of_cell[j] + 2; k++)
                        cout << link;
                    cout << middle_line_separator;
                }
                cout << right_line_separator << '\n';
            }
            
            cout << separator;
            for (int j = 0; j < columns; j++)
            {
                if (j > 0)
                    cout << separator;
                cout << ' ' << content.substr(rand() % 26, 10) << ' ';
            }
            cout << separator << '\n';
        }
        
        cout << bottom_left_corner;
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < length_of_cell[i] + 2; j++)
                cout << link;
            cout << bottom_line_separator;
        }
        cout << bottom_right_corner << '\n';
    }
    
    return 0;
}
