#include <iostream>
#include <cstdlib>

using namespace std;

// 转向
string cmds[7] = {
    "TURN LEFT", "TURN RIGHT", "TURN HALF LEFT", "TURN HALF RIGHT",
    "TURN SHARP LEFT", "TURN SHARP RIGHT", "GO"
};

int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_HALF_LEFT = 2, TURN_HALF_RIGHT = 3,
    TURN_SHARP_LEFT = 4, TURN_SHARP_RIGHT = 5, GO = 6;

string directions[4] = {
    "W", "E", "N", "S"
};

int main(int argc, char *argv[])
{
    for (int s = 1; s <= 100; s++)
    {
            cout << "A";
            cout << rand() % 50 + 1;
            cout << directions[rand() % 2];
            cout << " S";
            cout << rand() % 50 + 1;
            cout << directions[rand() % 2 + 2];
            cout << " " << directions[rand() % 4] << endl;
            
        for (int i = 1; i <= 100; i++)
        {
            int index = rand() % 7;
            cout << cmds[index];
            if (index == 6)
                cout << " " << (rand() % 99 + 1);
            cout << endl;
            
        }
        cout << "STOP" << endl;
    }
    cout << "END" << endl;
    
    return 0;
}
