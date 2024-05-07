import java.util.*;

// 用Java写一下，相比acwing291.cpp从列考虑，这里从行考虑
public class AcWing291 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        final int N = 12;
        long[][] f = new long[12][1 << N]; // f[i][j]表示第i行的状态
        boolean[] state = new boolean[1 << N];
        while (true) {
            int n = input.nextInt();
            int m = input.nextInt();
            if (n == 0 && m == 0) break;
            // 每一行的状态需要m位
            for (int i = 0; i < 1 << m; i++) {
                int count = 0;
                state[i] = true;
                for (int j = 0; j < m; j++) {
                    if (((i >> j) & 1) == 1) {
                        if ((count & 1) > 0) {
                            state[i] = false;
                            break;
                        }
                        else count = 0;
                    }
                    else count++;
                }
                if ((count & 1) > 0) state[i] = false;
            }
            for (long[] arr : f) Arrays.fill(arr, 0);
            f[0][0] = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j < 1 << m; j++) {
                    for (int k = 0; k < 1 << m; k++) {
                        if ((j & k) == 0 && state[j | k]) {
                            f[i][j] += f[i - 1][k];
                        }
                    }
                }
            }
            System.out.println(f[n][0]);
        }
        input.close();
    }
}

// 用时比C++短，591ms