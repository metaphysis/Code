// Correct Move
// UVa ID: 255
// Verdict: Accepted
// Submission Date: 2016-05-12
// UVa Run Time: 0.110s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isLegalMove(int king, int queen, int move)
{
    set < int > next;
    
    for (int i = queen - 8; i >= 0; i -= 8)
    {
        if (i == king)
            break;
        next.insert(i);
    }
            
    for (int i = queen + 8; i < 64; i += 8)
    {
        if (i == king)
            break;
        next.insert(i);
    }
    
    for (int i = queen - 1; i >= (queen / 8) * 8; i--)
    {
        if (i == king)
            break;
        next.insert(i);
    }
    
    for (int i = queen + 1; i < (queen / 8 + 1) * 8; i++)
    {
        if (i == king)
            break;
        next.insert(i);
    }
            
    return next.count(move) > 0;
}

bool isAllowedMove(int king, int move)
{
    if ((king - 8) >= 0 && (king - 8) == move)
        return false;
            
    if ((king + 8) < 64 && (king + 8) == move)
        return false;
        
    if ((king - 1) >= (king / 8 * 8) && (king - 1) == move)
        return false;
    
    if ((king + 1) < ((king / 8 + 1) * 8) && (king + 1) == move)
        return false;
        
    return true;
}

bool isStop(int king, int queen)
{
    set < int > disallowed;
    
    for (int i = queen; i >= 0; i -= 8)
        disallowed.insert(i);
            
    for (int i = queen; i < 64; i += 8)
        disallowed.insert(i);
            
    for (int i = (queen / 8) * 8; i < (queen / 8 + 1) * 8; i++)
        disallowed.insert(i);
            
    if ((king - 8) >= 0 && disallowed.count((king - 8)) == 0)
        return false;
            
    if ((king + 8) < 64 && disallowed.count((king + 8)) == 0)
        return false;
        
    if ((king - 1) >= (king / 8 * 8) && disallowed.count((king - 1)) == 0)
        return false;
    
    if ((king + 1) < ((king / 8 + 1) * 8) && disallowed.count((king + 1)) == 0)
        return false;
        
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int king, queen, move;
    while (cin >> king >> queen >> move)
    {
        if (king == queen)
        {
            cout << "Illegal state\n";
            continue;
        }
        
        if (isLegalMove(king, queen, move) == false)
        {
            cout << "Illegal move\n";
            continue;
        }
        
        if (isAllowedMove(king, move) == false)
        {
            cout << "Move not allowed\n";
            continue;
        }
        
        queen = move;
        
        if (isStop(king, queen))
            cout << "Stop\n";
        else
            cout << "Continue\n";
    }
    
	return 0;
}
