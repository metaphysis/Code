// Back to the Past
// UVa ID: 13025
// Verdict: Accepted
// Submission Date: 2019-02-25
// UVa Run Time: 0.060s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Calendar c = Calendar.getInstance();
        c.set(2019, 4, 29);
        String[] dayNames = new String[] {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        System.out.println("May 29, 2013 " + dayNames[c.get(Calendar.DAY_OF_WEEK) - 1]);
    }   
}
