/*
url: https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/?envType=daily-question&envId=2023-11-24
LeetCode参考: https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/solutions/2396216/onlogn-pai-xu-shuang-zhi-zhen-by-endless-qk40/
相关: LeetCode1. 两数之和
标签: 排序, 二分查找, 双指针
*/

import java.util.*;

public class Solution2824 {
    public int countPairs(List<Integer> nums, int target) {
        Collections.sort(nums);
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            // 搜索最后一个小于target - nums[i]的位置
            ans += binSearch(nums, i + 1, target - nums.get(i)) - i;
        }
        return ans;
    }

    private int binSearch(List<Integer> nums, int index, int upperbound) {
        // 左闭右开写法，最终left - 1范围为[index-1, right)
        int left = index, right = nums.size();
        while (left < right) {
            int mid = (left + right) >> 1;
            if (nums.get(mid) < upperbound) left = mid + 1;
            else right = mid;
        }
        return left - 1;
    }

    // 参考<https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/solutions/2396216/onlogn-pai-xu-shuang-zhi-zhen-by-endless-qk40/>，用双指针更好
    public int countPairs_implementation2(List<Integer> nums, int target) {
        Collections.sort(nums);
        int ans = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums.get(left) + nums.get(right);
            if (sum < target) {
                ans += right - left; // 此时任意(left, right]与left组合都满足和小于target
                left++;
            }
            else right--;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2824 solu = new Solution2824();
        System.out.println(solu.countPairs(Arrays.asList(6,-1,7,4,2,3), 8));
        System.out.println(solu.countPairs_implementation2(Arrays.asList(6,-1,7,4,2,3), 8));
    }
}
