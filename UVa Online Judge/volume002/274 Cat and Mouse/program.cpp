// Cat and Mouse
// UVa IDs: 274
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int cat[101][101], mouse[101][101], mouseSecond[101][101];
int roomNumber, catHome, mouseHome;

void findWalk()
{
    for (int k = 0; k < roomNumber; k++)
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++)
            {
                if (cat[i][k] + cat[k][j] < cat[i][j])
                    cat[i][j] = cat[i][k] + cat[k][j];
                    
                if (mouse[i][k] + mouse[k][j] < mouse[i][j])
                    mouse[i][j] = mouse[i][k] + mouse[k][j];
            }
            
    bool findRoom = false;
    for (int i = 0; i < roomNumber; i++)
        if (cat[catHome][i] < 10000 && mouse[mouseHome][i] < 10000)
        {
            findRoom = true;
            break;
        }
        
    cout << (findRoom ? "Y" : "N");
    
    for (int i = 0; i < roomNumber; i++)
        if (cat[catHome][i] < 10000)
        {
            for (int j = 0; j < roomNumber; j++)
            {
                mouseSecond[j][i] = 0;
                mouseSecond[i][j] = 0;
            }
        }
            
    for (int k = 0; k < roomNumber; k++)
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++)
            {
                if (mouseSecond[i][k] < 0 && mouseSecond[k][j] < 0 &&    
                    mouseSecond[i][k] + mouseSecond[k][j] < mouseSecond[i][j])
                    mouseSecond[i][j] = mouseSecond[i][k] + mouseSecond[k][j];
            }
            
    int longestWalk = abs(mouseSecond[mouseHome][mouseHome]);
    
    cout << (longestWalk >= 2 ? " Y" : " N") << endl;
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;
    
    while (cases--)
    {
        cin >> roomNumber >> catHome >> mouseHome;
        catHome--;
        mouseHome--;
        
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++)
            {
                cat[i][j] = 10000;
                mouse[i][j] = 10000;
                mouseSecond[i][j] = 0;
            }
        
        cat[catHome][catHome] = 1;
        mouse[mouseHome][mouseHome] = 1;
            
        int start, end;
        while (cin >> start >> end, start > 0 && end > 0)
            cat[start - 1][end - 1] = 1;
        
        cin.ignore();
        string line;
        while (getline(cin, line), line.length() > 0)
        {
            sscanf(line.data(), "%d %d", &start, &end);
            mouse[start - 1][end - 1] = 1;
            mouseSecond[start - 1][end - 1] = -1;
        }
        
        findWalk();
        
        if (cases)
            cout << endl;
    }
    
	return 0;
}
