/*
url: https://leetcode.cn/problems/two-sum/
相关: LeetCode2824. 统计和小于目标的下标对数目
标签: 标号数组排序, 双指针
*/

import java.util.*;

public class Solution1 {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        int[] ans = new int[2];
        for (int i = 0; i < nums.length; i++) map.put(nums[i], i);
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i]) && map.get(target - nums[i]) != i) {
                ans[0] = i;
                ans[1] = map.get(target - nums[i]);
                break;
            }
        }
        return ans;
    }

    // 另外一种写法，遍历nums过程中逐步向map中put，map中只存i前面的数
    public int[] twoSum_implementation2(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        int[] ans = new int[2];
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i])) {
                ans[0] = i;
                ans[1] = map.get(target - nums[i]);
                break;
            }
            map.put(nums[i], i);
        }
        return ans;
    }

    // 用标号数组排序 + 双指针，开销大不过也是一种思路
    public int[] twoSum_implementation3(int[] nums, int target) {
        int n = nums.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, (i, j) -> nums[i] - nums[j]);
        int left = 0, right = idx.length - 1;
        while (left < right) {
            int sum = nums[idx[left]] + nums[idx[right]];
            if (sum == target) return new int[]{idx[left], idx[right]};
            else if (sum > target) right--;
            else left++;
        }
        return null;
    }

    public static void main(String[] args) {
        Solution1 solu = new Solution1();
        System.out.println(Arrays.toString(solu.twoSum(new int[]{2,7,11,15}, 9)));
        System.out.println(Arrays.toString(solu.twoSum_implementation2(new int[]{2,7,11,15}, 9)));
        System.out.println(Arrays.toString(solu.twoSum_implementation3(new int[]{2,7,11,15}, 9)));
    }
}
