/*
url: https://leetcode.cn/problems/largest-element-in-an-array-after-merge-operations/description/?envType=daily-question&envId=2024-03-14
LeetCode参考: https://leetcode.cn/problems/largest-element-in-an-array-after-merge-operations/solutions/2679835/he-bing-hou-shu-zu-zhong-de-zui-da-yuan-s2b5o/
              https://leetcode.cn/problems/largest-element-in-an-array-after-merge-operations/solutions/2685894/cong-bao-li-mei-ju-dao-yi-ci-bian-li-pyt-jjta/
标签: 贪心, 逆序遍历
*/

import java.util.*;

public class Solution2789 {
    // 这样不对，对[2,3,7,9,3]这个用例，要2,3结合，7,9结合，然后5,16才能结合获取最大值，说明需要一定的枚举，尝试dp，但是dp也能感觉出来不行
    public long maxArrayValue_wrong(int[] nums) {
        Deque<Long> stack = new LinkedList<>();
        long ans = 0;
        for (int i = 0; i < nums.length; i++) {
            long x = nums[i];
            while (!stack.isEmpty() && stack.peek() <= x) {
                x += stack.pop();
            }
            stack.push(x);
            ans = Math.max(ans, x);
        }
        return ans;
    }

    // 这里不行的原因是这里子问题不是分割得很好，对[2,3,7,9,3]这个用例就能看出来需要一定的结合顺序，然后能把2,3,7,9合成21
    public long maxArrayValue_wrong2(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n]; // dp[i]表示以nums[i]为一个融合结尾所能获得的最大值
        dp[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] <= nums[i]) {
                    dp[i] = Math.max(dp[i], dp[j] + nums[i]);
                    ans = Math.max(ans, dp[i]);
                }
            }
        }
        return ans;
    }

    /* 逆序遍历，nums元素全为正，这样操作能让nums[i]能尽量小，nums[i+1]能尽量大，就能尽可能地合并出最大值。
    这里由于合并后和会变大，因此'大'和'小'的地位不相同，有一定的不对称性，所以逆序遍历能起作用。这里合并出的最大值一定会在第一个位置。
    */
    public long maxArrayValue(int[] nums) {
        int n = nums.length;
        long ans = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > ans) {
                ans = nums[i];
            }
            else ans += nums[i];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2789 solu = new Solution2789();
        System.out.println(solu.maxArrayValue(new int[]{2,3,7,9,3}));
    }
}
