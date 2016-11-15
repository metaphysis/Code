// It's Ir-Resist-Able!
// UVa ID: 345
// Verdict: Accepted
// Submission Date: 2016-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

const int MAXN = 100;
const double EPSICON = 1e-8;

// 不考虑其他节点影响时，两个节点间的电阻。
double resistor[MAXN][MAXN];

// 两个节点间的电势。
double voltage[MAXN];

// 列主元高斯消元法求解线性方程组Ax=b。
bool gaussianElimination(vector<vector<double>> &A, vector<double> &b)
{
    // 把b存放在A的右边以方便后续处理。
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        // 为减少误差，将正在处理的未知元系数的绝对值最大的方程式与第i个方程式交换。
        int pivot = i;
        for (int j = i; j < n; j++)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]);

        // 方程组无解或具有无穷多个解。
        if (fabs(A[i][i]) < EPSICON) return false;

        // 把正在处理的未知元的系数变为1。
        for (int j = i + 1; j <= n; j++) A[i][j] /= A[i][i];

        // 从第j个式子中消去第i个未知元。
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++) A[j][k] -= A[j][i] * A[i][k];
    }

    // 存放在矩阵A最右边的元素即为解。
    for (int i = 0; i < n; i++) b[i] = A[i][n];
    
    return true;
}

int main(int argc, char *argv[])
{
    int N, A, B, X, Y, cases = 0;
    double R;

    while (cin >> N >> A >> B, N > 0)
    {
        cout << "Case " << ++cases << ": ";

        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                resistor[i][j] = 0.0;

        map<int, int> indexer;
        
        for (int i = 0, label = 0; i < N; i++)
        {
            cin >> X >> Y >> R;

            if (indexer.find(X) == indexer.end()) indexer[X] = label++;
            if (indexer.find(Y) == indexer.end()) indexer[Y] = label++;
            
            resistor[indexer[X]][indexer[Y]] += 1.0 / R;
            resistor[indexer[Y]][indexer[X]] += 1.0 / R;
        }

        int C = indexer.size();

        // 求出两个连接点之间直接相连的并联电阻的等效电阻。
        for (int i = 0; i < C; i++)
            for (int j = 0; j < C; j++)
                resistor[i][j] = 1.0 / resistor[i][j];

        vector<vector<double>> matrix(C, vector<double>(C, 0.0));
        vector<double> voltage(C, 0.0);

        // 节点电势，取起点电势为1000，终点电势为0。
        voltage[indexer[A]] = 1000.0;
        voltage[indexer[B]] = 0.0;

        // 由于起点和终点的电势为已知预设值，构建方程使得方程组所对应的矩阵为方阵。
        matrix[indexer[A]][indexer[A]] = matrix[indexer[B]][indexer[B]] = 1.0;

        // 构建由电势未知元形成的方程组。
        for (int node = 0; node < C; node++)
        {
            // 起点和终点的电势已经预设，不需再建立方程式。
            if (node == indexer[A] || node == indexer[B]) continue;

            for (int other = 0; other < C; other++)
                if (resistor[node][other] > EPSICON)
                {
                    // 单位电势下从node流到other的电流。
                    double inI = 1.0 / resistor[node][other];

                    // 基尔霍夫电流定律：所有进入某节点的电流与所有离开该节点的
                    // 电流数值的代数和为零。
                    matrix[node][other] += inI;
                    matrix[node][node] -= inI;
                }
        }

        // 使用列主元高斯消除法求解各节点的电势。
        gaussianElimination(matrix, voltage);

        // 计算终点流入的电流之和。
        double current = 0.0;
        for (int node = 0; node < C; node++)
            if (resistor[node][indexer[B]] > EPSICON)
                current += (voltage[node] - voltage[indexer[B]]) /
                    resistor[node][indexer[B]];

        // 根据欧姆定律计算等效阻值。
        if (fabs(current) < EPSICON)
            cout << "0.00 Ohms\n";
        else
        {
            cout << fixed << setprecision(2);
            cout << (voltage[indexer[A]] - voltage[indexer[B]]) / current;
            cout << " Ohms\n";
        }
    }

    return 0;
}
