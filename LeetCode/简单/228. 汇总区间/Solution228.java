/*
url: https://leetcode.cn/problems/summary-ranges/
标签: 双指针
*/

import java.util.ArrayList;
import java.util.List;

public class Solution228 {
    public List<String> summaryRanges(int[] nums) {
        List<String> ans = new ArrayList<>();
        int left = 0, right = left;
        while (true) {
            if (left >= nums.length) break;
            right += 1;
            if (right >= nums.length) {
                if (left == right - 1) ans.add(String.valueOf(nums[left]));
                else ans.add(nums[left] + "->" + nums[right - 1]);
                break;
            }
            if (nums[right] - nums[left] != right - left) {
                if (left == right - 1) ans.add(String.valueOf(nums[left]));
                else ans.add(nums[left] + "->" + nums[right - 1]);
                left = right;
                right = left;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution228 solu = new Solution228();
        System.out.println(solu.summaryRanges(new int[]{-2147483648,-2147483647,2147483647}));
    }
}