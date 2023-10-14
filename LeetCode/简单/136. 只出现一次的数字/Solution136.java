/*
url: https://leetcode.cn/problems/single-number/?envType=daily-question&envId=2023-10-14
LeetCode参考: https://leetcode.cn/problems/single-number/solutions/242211/zhi-chu-xian-yi-ci-de-shu-zi-by-leetcode-solution/
相关: LeetCode137. 只出现一次的数字 II
标签: 异或的特殊性质
*/

import java.util.Arrays;

public class Solution136 {
    public int singleNumber(int[] nums) {
        Arrays.sort(nums);
        for (int i = 0; i < nums.length;) {
            if (i + 1 < nums.length && nums[i] == nums[i + 1]) {
                i = i + 2;
                continue;
            }
            else {
                return nums[i];
            }
        }
        return nums[nums.length - 1];
    }

    public int singleNumber_implementation2(int[] nums) {
        int ans = 0;
        // a ^ a = 0，0又是异或运算的单位元，所以出现两次的数全异或掉了
        for (int i = 0; i < nums.length; i++) {
            ans ^= nums[i];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution136 solu = new Solution136();
        System.out.println(solu.singleNumber(new int[]{2,2,1}));
    }
}
