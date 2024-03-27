import java.util.*;

class P1002 {
    public static void main(String[] args) {
        int n, m;
        int x, y;
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        m = input.nextInt();
        x = input.nextInt();
        y = input.nextInt();
        input.close();
        Set<Integer> set = new HashSet<>();
        // 1 <= n,m <= 20, 用进制表示法, 这里马的禁止走的坐标可能为负，D弄大点
        final int D = 101;
        set.add(x * D + y);
        int[][] directions = new int[][]{{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
        set.add(x * D + y);
        for (int[] arr : directions) {
            set.add((x + arr[0]) * D + y + arr[1]);
        }
        long[][] dp = new long[n + 1][m + 1];
        dp[0][0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) continue;
                if (set.contains(i * D + j)) continue;
                dp[i][j] = (j - 1 >= 0 ? dp[i][j - 1] : 0) + (i - 1 >= 0 ? dp[i - 1][j] : 0);
            }
        }
        System.out.println(dp[n][m]);
    }
}