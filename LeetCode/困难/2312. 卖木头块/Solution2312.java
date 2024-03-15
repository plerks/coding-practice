/*
url: https://leetcode.cn/problems/selling-pieces-of-wood/description/?envType=daily-question&envId=2024-03-15
LeetCode参考: https://leetcode.cn/problems/selling-pieces-of-wood/solutions/1611240/by-endlesscheng-mrmd/
              https://leetcode.cn/problems/selling-pieces-of-wood/solutions/1630619/mai-mu-tou-kuai-by-leetcode-solution-gflg/
相关: LeetCode1444. 切披萨的方案数
标签: 动态规划, 切矩形
*/

import java.util.*;

public class Solution2312 {
    // 52 / 60 个通过的测试用例，超时
    public long sellingWood_exceed_time_limit(int m, int n, int[][] prices) {
        long[][] dp = new long[n + 1][m + 1]; // dp[i][j]表示切一块i*j大小的的最大收益
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int[] arr : prices) {
                    int h = arr[0], w = arr[1], price = arr[2];
                    if (i >= w && j >= h) {
                        dp[i][j] = Math.max(dp[i][j], price + dp[i - w][j] + dp[w][j - h]);
                    }
                }
            }
        }
        return dp[n][m];
    }

    /* 针对上面的超时做优化，1 <= prices.length <= 2 * 10^4，prices可能很长，57 / 60 个通过的测试用例。
    对5, 5, new int[][]{{1,5,2},{1,4,3},{2,5,1},{2,3,3},{1,3,2},{2,4,4},{5,5,4},{4,1,1},{3,3,2},{3,1,2},{2,2,3}}这个用例解答错误。
    */
    public long sellingWood_wrong(int m, int n, int[][] prices) {
        Arrays.sort(prices, (x, y) -> x[0] - y[0]);
        long[][] dp = new long[n + 1][m + 1]; // dp[i][j]表示切一块i*j大小的的最大收益
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int[] arr : prices) {
                    int h = arr[0], w = arr[1], price = arr[2];
                    if (h > j) break;
                    if (i >= w && j >= h) {
                        /* 切w*h一块，(i-w)*j和w*(j-h)是子问题。
                        假如对于5*3的初始面积，切一块2*2的，(i-w)*j和w*(j-h)都无法容纳下4*1的，但是剩余的整个面积是可以容纳4*1的，
                        这是否导致问题？没发生，因为后面还会考虑对5*3的初始面积第一步切4*1的。(仅仅是对3, 5, [[1,4,2],[2,2,7],[2,1,3]]这个用例没发生)

                        问题也就是，最佳切割方案是否会因为总是要跨(i-w)*j和w*(j-h)这两个区域而导致这样切割子问题出错？
                        一个错误的想法是：若第一步切w*h，然后分割为(i-w)*j和w*(j-h)两个子问题无法得出最优解，则说明最优解至少有一块要穿过剩下的两个区域，
                        而这种情况会在考虑第一块切的是最长块(指水平方向最长)时考虑到，因此不会出问题。

                        既然有用例过不了(那个用例的正确值比这样计算出来的大，虽然这里题意理解错了，想的是填充，但是这里方案是更自由的，不该得出更小的结果)，说明
                        有可能总是无法避免跨越，也就是子问题分割不成立。

                        若切割方式相同(即切割所使用的子块完全相同)，但排布不同，是否能通过重新排列变为相同的切割？
                        是，考虑切割是个满的切割，最终没有空隙。则只需把对应的块移向目标位置即可。若有空隙，则假想把空隙添上新的块，则问题转为满的切割。
                        也就是说，这里切割矩形不需考虑内部排布，只需考虑内部成分，切好之后排布是任意的。

                        再考虑一下这个问题，是否能以这样的方式计算填充矩形的最大收益：
                        枚举左上角为w*h的一块，假定左上角为这一块的情况下的最优解不会发生跨越，然后进行计算。
                        问题相当于，是否一定存在一个最优解，其对于左上角的那一块没有发生跨越。
                        应该是不能，虽然不确定，但是问题还有一个关键点在于跨越不一定由最长块引起，有可能输入就是能使得排布很满，一个短的矩形都可能引起
                        跨越，也就是说就算左上角那块很长也算不了什么。
                        待做: 构造一个输入，使得对于填充矩形的最大收益问题，所有最优解对于左上角的那一块都发生跨越。感觉这个输入不好构造
                        */
                        dp[i][j] = Math.max(dp[i][j], price + dp[i - w][j] + dp[w][j - h]);
                    }
                }
            }
        }
        return dp[n][m];
    }

    /* 上面的想法不太对，想的是填充，但是这题和`LeetCode1444. 切披萨的方案数`一样，水平竖直切是要**完全**切开，这样水平切一刀竖直方向就不会再有跨越的问题，
    上面分成(i-w)*j就不对，竖直方向已经不够j了。
    */
    public long sellingWood(int m, int n, int[][] prices) {
        long[][] dp = new long[n + 1][m + 1]; // dp[i][j]表示切一块i*j大小的的最大收益
        for (int[] arr : prices) {
            int h = arr[0], w = arr[1], price = arr[2];
            dp[w][h] = price;
        }
        for (int w = 0; w <= n; w++) {
            for (int h = 0; h <= m; h++) {
                for (int i = 1; i <= h - 1; i++) { // 水平切，上面一块的高
                    dp[w][h] = Math.max(dp[w][h], dp[w][i] + dp[w][h - i]);
                }
                for (int i = 1; i <= w - 1; i++) { // 竖直切，左边一块的宽
                    dp[w][h] = Math.max(dp[w][h], dp[i][h] + dp[w - i][h]);
                }
            }
        }
        return dp[n][m];
    }

    // 参考灵茶山艾府的题解，枚举水平竖直切的情况时只需枚举一半情况就行，是对称的
    public long sellingWood_implementation2(int m, int n, int[][] prices) {
        long[][] dp = new long[n + 1][m + 1]; // dp[i][j]表示切一块i*j大小的的最大收益
        for (int[] arr : prices) {
            int h = arr[0], w = arr[1], price = arr[2];
            dp[w][h] = price;
        }
        for (int w = 0; w <= n; w++) {
            for (int h = 0; h <= m; h++) {
                for (int i = 1; i <= h / 2; i++) { // 水平切，上面一块的高
                    dp[w][h] = Math.max(dp[w][h], dp[w][i] + dp[w][h - i]);
                }
                for (int i = 1; i <= w / 2; i++) { // 竖直切，左边一块的宽
                    dp[w][h] = Math.max(dp[w][h], dp[i][h] + dp[w - i][h]);
                }
            }
        }
        return dp[n][m];
    }

    public static void main(String[] args) {
        Solution2312 solu = new Solution2312();
        // System.out.println(solu.sellingWood(3, 5, new int[][]{{1,4,2},{2,2,7},{2,1,3}}));
        // System.out.println(solu.sellingWood(4, 6, new int[][]{{3,2,10},{1,4,2},{4,1,3}}));
        // System.out.println(solu.sellingWood(5, 5, new int[][]{{1,5,2},{1,4,3},{2,5,1},{2,3,3},{1,3,2},{2,4,4},{5,5,4},{4,1,1},{3,3,2},{3,1,2},{2,2,3}}));
        System.out.println(solu.sellingWood(8, 9, new int[][]{{6,3,17},{6,4,25}}));
        System.out.println(solu.sellingWood_implementation2(8, 9, new int[][]{{6,3,17},{6,4,25}}));
    }
}
