// Electricity
// UVa ID: 12148
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.360s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int n;
        while ((n = scan.nextInt()) > 0) {
            int days = 0, consumption = 0;
            int D1, M1, Y1, C1, D2, M2, Y2, C2;

            Calendar c = Calendar.getInstance();

            D1 = scan.nextInt(); M1 = scan.nextInt(); Y1 = scan.nextInt();
            C1 = scan.nextInt();

            for (int i = 1; i < n; i++) {
                D2 = scan.nextInt(); M2 = scan.nextInt(); Y2 = scan.nextInt();
                C2 = scan.nextInt();

                c.set(Y1, M1 - 1, D1);
                c.add(Calendar.DAY_OF_MONTH, 1);

                D1 = c.get(Calendar.DAY_OF_MONTH);
                M1 = c.get(Calendar.MONTH) + 1;
                Y1 = c.get(Calendar.YEAR);

                if (D1 == D2 && M1 == M2 && Y1 == Y2) {
                    days++;
                    consumption += C2 - C1;
                }
                D1 = D2; M1 = M2; Y1 = Y2; C1 = C2;
            }

            System.out.printf("%d %d\n", days, consumption);
        }
    }
}
