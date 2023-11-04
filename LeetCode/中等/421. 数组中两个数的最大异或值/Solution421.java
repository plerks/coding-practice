/*
url: https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/?envType=daily-question&envId=2023-11-04
LeetCode参考: https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/solutions/778291/shu-zu-zhong-liang-ge-shu-de-zui-da-yi-h-n9m9/
标签: 异或的特殊性质
*/

import java.util.HashSet;

public class Solution421 {
    public int findMaximumXOR(int[] nums) {
        int x = 0;
        HashSet<Integer> set = new HashSet<>();
        for (int i = 30; i >= 0; i--) { // 确定每一位，题目给定num[i]>=0
            set.clear();
            for (int val : nums) {
                set.add(val >> i);
            }
            // 目前x是从最高位到i+1位已找出的最大可能
            int xNext = 2 * x + 1; // 尝试将x的下一位置为1
            boolean found = false;
            for (int val : set) {
                // 异或的特殊性质，想找两个数a，b使得a ^ b = x，等价于找a ^ x = b
                if (set.contains(xNext ^ val)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                x = 2 * x;
            }
            else x = xNext;
        }
        return x;
    }

    public static void main(String[] args) {
        Solution421 solu = new Solution421();
        System.out.println(solu.findMaximumXOR(new int[]{3,10,5,25,2,8}));
    }
}