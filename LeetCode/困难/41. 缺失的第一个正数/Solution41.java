/*
url: https://leetcode.cn/problems/first-missing-positive/
LeetCode参考: https://leetcode.cn/problems/first-missing-positive/solutions/304743/que-shi-de-di-yi-ge-zheng-shu-by-leetcode-solution/
相关: LeetCode2003. 每棵子树内缺失的最小基因值
*/

public class Solution41 {
    public int firstMissingPositive(int[] nums) {
        // 一旦nums不让1,2,...n同时出现（此时最小未出现为n + 1），则最小未出现正整数一定为[1,n]间的一个数字
        int n = nums.length;
        int[] map = new int[n];
        for (int i = 0; i < n; i++) {
            if (1 <= nums[i] && nums[i] <= n) {
                map[nums[i] - 1] = 1;
            }
        }
        int ans = n + 1;
        for (int i = 0; i < n; i++) {
            if (map[i] == 0) {
                ans = i + 1;
                break;
            }
        }
        return ans;
    }

    // 题目要求空间复杂度O(1)的解法
    public int firstMissingPositive_implementation2(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            // 把值换到其应该在的位置上
            while (1 <= nums[i] && nums[i] <= n && nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]) {
                /* int temp = nums[i];
                nums[i] = nums[nums[i] - 1];
                nums[nums[i] - 1] = temp; */ // 这样写不行，第三行左边的nums[i]变了，改成nums[temp - 1] = temp;可以

                int temp = nums[nums[i] - 1];
                nums[nums[i] - 1] = nums[i];
                nums[i] = temp;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }

    public static void main(String[] args) {
        Solution41 solu = new Solution41();
        System.out.println(solu.firstMissingPositive(new int[]{1,2,0}));
        System.out.println(solu.firstMissingPositive_implementation2(new int[]{3,4,-1,1}));
    }
}
