/*
url: https://leetcode.cn/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/description/
LeetCode参考: https://leetcode.cn/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/solutions/2704767/liang-chong-fang-fa-mei-ju-o1-shu-xue-go-ug47/
标签: LeetCode第390场周赛, 贪心
*/

// 此题属于我参加的LeetCode第390场周赛
public class Solution3091 {
    /* 周赛时的解法，通过。
    +1的操作一定是放在最前面的，复制元素时一定是复制最大值，假设操作序列+1不在最前面，则将
    +1全部移动到最前且后面复制更大的最大值一定是更佳方案。
    灵茶山艾府题解这里向上取整时有细微不同，是用的⌈k/m⌉-1 = ⌊(k-1)/m⌋这个关系
    */
    public int minOperations(int k) {
        int ans = Integer.MAX_VALUE;
        // 枚举+1次数
        for (int i = 0; i < k; i++) {
            int max = 1 + i;
            int count = i + (k - i - 1 + max - 1) / max; // + max - 1是为了向上取整
            ans = Math.min(ans, count);
        }
        return ans;
    }

    /* 灵茶山艾府题解解法，设m = 1 + add次数，则ans为y = min{m-1+⌊(k-1)/m⌋}，m为自变量，而双勾函数f(x) = x + m / x在根号x处取最小，因此只需试⌊sqrt(k-1)⌋和⌊sqrt(k-1)⌋+1两个位置。
    
    这里y = min{m-1+⌊(k-1)/m⌋}里面还有个取整与对勾函数不完全相同，不会影响正确性。对于y = m + (k-1)/m（m为整数），其一定在⌊sqrt(k-1)⌋或⌊sqrt(k-1)⌋+1取最小值，所需担心的是对于
    y = m + ⌊(k-1)/m⌋，是否在其它位置会因为取整更小使得其它位置的y更小？
    结论是不会，记p1 = ⌊sqrt(k-1)⌋, p2 = ⌊sqrt(k-1)⌋ + 1，现证p1和p2位置一定能取得y = m + ⌊(k-1)/m⌋的最小值
    1. 在p1左侧，当m < p1时，已知m + (k-1)/m > p1 + (k-1)/p1，现证一定会有m + ⌊(k-1)/m⌋ >= p1 + ⌊(k-1)/p1⌋。
        证明: 设(k-1)/m = n1 + r1, (k-1)/p1 = n2 + r2 (n为整数部分，r为小数部分)，则有m - p1 > n2 - n1 + r2 - r1，要证m - p1 >= ⌊(k-1)/p1⌋ - ⌊(k-1)/m⌋ = n2 - n1
        若-1 < r2 - r1 <= 0，由于m - p1为整数，则m - p1 > n2 - n1 + r2 - r1 => m - p1 >= n2 - n1，得证
        若0 < r2 - r1 < 1，则m - p1 > n2 - n1 + r2 - r1 > n2 - n1，得证
    2. 在p2右侧，同理可证
    所以只需试p1和p2位置即可
    此外，这里这里开方会不会因为精度问题导致错误，见LeetCode2594. 修车的最少时间
    */
    public int minOperations_implementation2(int k) {
        int p1 = Math.max((int)Math.sqrt(k - 1), 1), p2 = p1 + 1;
        return Math.min(p1 - 1 + (k - 1) / p1, p2 - 1 + (k - 1) / p2);
    }

    public static void main(String[] args) {
        Solution3091 solu = new Solution3091();
        System.out.println(solu.minOperations(11));
        System.out.println(solu.minOperations_implementation2(11));
    }
}
