// Making the Grade
// UVa ID: 381
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct student
{
    double average;
    int bouns, absences, grade;
};

double roundToTenth(double number)
{
    return (int)(number * 10.0 + 0.5) / 10.0;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    vector <student> students;
    int N, S, T;
    cin >> N;

    cout << "MAKING THE GRADE OUTPUT" << endl;
    for (int i = 1; i <= N; i++)
    {
        cin >> S >> T;

        students.clear();
        for (int j = 1; j <= S; j++)
        {
            double lowest = 100.0, sumOfScores = 0.0, score;
            for (int k = 1; k <= T; k++)
            {
                cin >> score;
                sumOfScores += score;
                lowest = min(lowest, score);
            }

            student aStudent;
            cin >> aStudent.bouns >> aStudent.absences;
            if (T > 2) aStudent.average = roundToTenth((sumOfScores - lowest) / (T - 1));
            else aStudent.average = sumOfScores / T;
            students.push_back(aStudent);
        }

        double sumOfPoints = 0.0, mean, sd;
        for (int i = 0; i < students.size(); i++) sumOfPoints += students[i].average;
        mean = roundToTenth(sumOfPoints / S);
        for (int i = 0; i < students.size(); i++) sd += pow(students[i].average - mean, 2);
        sd = roundToTenth(sqrt(sd / S));

        double sumOfGrade = 0;
        for (int i = 0; i < students.size(); i++)
        {
            students[i].average = roundToTenth(students[i].average + 3.0 * (students[i].bouns / 2));

            if (students[i].average >= (mean + sd)) students[i].grade = 4;
            else if (students[i].average >= mean) students[i].grade = 3;
            else if (students[i].average >= (mean - sd)) students[i].grade = 2;
            else students[i].grade = 1;

            if (students[i].absences > 0) students[i].grade -= students[i].absences / 4;
            else students[i].grade++;

            if (students[i].grade < 0) students[i].grade = 0;
            else if (students[i].grade > 4) students[i].grade = 4;

            sumOfGrade += students[i].grade;
        }

        cout << fixed << setprecision(1) << (sumOfGrade / S) << endl;
    }
    cout << "END OF OUTPUT" << endl;

    return 0;
}
