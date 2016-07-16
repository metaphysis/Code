// Pattern Matching Prelims
// UVa ID: 250
// Verdict: Accepted
// Submission Date: 2016-05-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1E-6;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    vector < double > sumOfRows, sumOfColumns;
    
    int row, column, cases = 0;
    while (cin >> row >> column, row && column)
    {
        sumOfRows.clear();
        sumOfColumns.clear();
        
        sumOfRows.resize(row);
        sumOfColumns.resize(column);
        
        fill(sumOfRows.begin(), sumOfRows.end(), 0.0);
        fill(sumOfColumns.begin(), sumOfColumns.end(), 0.0);
        
        double value;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                cin >> value;
                sumOfRows[i] += value;
                sumOfColumns[j] += value;
            }
            
        for (int i = 1; i < sumOfRows.size(); i++)
            sumOfRows[i] += sumOfRows[i - 1];
            
        for (int j = 1; j < sumOfColumns.size(); j++)
            sumOfColumns[j] += sumOfColumns[j - 1];
        
        int minRow = row - 1;
        double minDifference = fabs(sumOfRows[row - 1]); 
        for (int i = row - 2; i >= 1; i--)
        {
            double temp = fabs(sumOfRows[row - 1] - sumOfRows[i] - sumOfRows[i - 1]);
            if (temp + EPSILON < minDifference)
            {
                minRow = i;
                minDifference = temp;
            }
        }
        
        int minColumn = column - 1;
        minDifference = fabs(sumOfColumns[column - 1]);
        for (int j = column - 2; j >= 1; j--)
        {
            double temp = fabs(sumOfColumns[column - 1] - sumOfColumns[j] - sumOfColumns[j - 1]);
            if (temp + EPSILON < minDifference)
            {
                minColumn = j;
                minDifference = temp;
            }
        }
        
        minRow++;
        minColumn++;
        
        cout << "Case " << ++cases;
        cout << ": center at (" << minRow << ", " << minColumn << ")" << endl;
    }
    
	return 0;
}
