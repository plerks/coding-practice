/*
url: https://leetcode.cn/problems/maximum-earnings-from-taxi/description/
标签: 动态规划
*/

import java.util.*;

public class Solution2008 {
    public long maxTaxiEarnings(int n, int[][] rides) {
        List<List<int[]>> map = new ArrayList<>();
        for (int i = 0; i < n + 1; i++) {
            map.add(new ArrayList<>());
        }
        for (int[] ride : rides) {
            map.get(ride[1]).add(ride);
        }
        long[] dp = new long[n + 1];
        long ans = 0;
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1]; // 没放下人
            // 刚放下一个人
            for (int[] ride : map.get(i)) {
                dp[i] = Math.max(dp[i], dp[ride[0]] + ride[1] - ride[0] + ride[2]);
            }
            ans = Math.max(ans, dp[i]);
        }
        return ans;
    }

    /* 这个Java代码在LeetCode上运行用时38ms，而C++我的两个实现用时是388ms和366ms，消耗内存也是Java更少，
    LeetCode1466. 重新规划路线官方题解的Java和C++实现对比也是，Java用时似乎有些过于短了，不过看到知乎上的回答:
    <https://www.zhihu.com/question/461560216/answer/2895703314>
    <https://www.zhihu.com/question/50137261/answer/119780292>
    <https://www.zhihu.com/question/528658985/answer/2661467570>
    <https://www.zhihu.com/question/456618030/answer/1856628789>
    大概是LeetCode后台Java的运行用时计算规则相比其它语言有优势，其它语言可能把外围代码的时间算进去了，Java没有。

    此外根据LeetCode上的C++报错信息，LeetCode后台加上了sanitizer检测地址错误等，所以运行也会变慢。
    */

    public static void main(String[] args) {
        Solution2008 solu = new Solution2008();
        System.out.println(solu.maxTaxiEarnings(5, new int[][]{{2,5,4}, {1,5,1}}));
    }
}
