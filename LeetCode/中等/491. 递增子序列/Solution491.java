/*
url: https://leetcode.cn/problems/non-decreasing-subsequences/
LeetCode参考: https://leetcode.cn/problems/non-decreasing-subsequences/solutions/387656/di-zeng-zi-xu-lie-by-leetcode-solution/
相关: https://leetcode.cn/problems/subsets/
标签: 幂集递归
*/

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Solution491 {
    private List<Integer> list = new ArrayList<>();
    private List<List<Integer>> ans = new ArrayList<>();
    private Set<Integer> set = new HashSet<>(); // 用于去重，[4,7,7]可能选出2个[4,7]
    private int radix = 0;

    public List<List<Integer>> findSubsequences(int[] nums) {
        /* radix取ai的最大值+1，相当于用radix进制来表示子数组，但是下面计算时每一位是要(list.get(i) + 101)，所以这里要取max{ai} + 102，但是
        不知道为什么max{ai} + 102还过不了所有用例，要max{ai} + 103 */
        for (int val : nums) {
            radix = Math.max(radix, val + 103);
        }
        for (int i = 0; i < nums.length; i++) {
            myFindSubsequences(nums, i);
        }
        return ans;
    }

    private void myFindSubsequences(int[] nums, int index) {
        if (list.isEmpty() || nums[index] >= list.get(list.size() - 1)) {
            list.add(nums[index]);
            int sum = 0, pow = 1;
            for (int i = 0; i < list.size(); i++) {
                sum += (list.get(i) + 101) * pow % (int) 1E9 + 7; // -100 <= nums[i] <= 100，+101是为了防止-1,0和-1,0,0...这样的序列计算出一样的值
                pow *= radix;
            }
            if (list.size() > 1 && !set.contains(sum)) {
                set.add(sum);
                ans.add(new ArrayList<>(list));
            }
            for (int i = index + 1; i < nums.length; i++) {
                myFindSubsequences(nums, i);
            }
            list.remove(list.size() - 1);
        }
    }

    public List<List<Integer>> findSubsequences_implementation2(int[] nums) {
        dfs(0, Integer.MIN_VALUE, nums);
        return ans;
    }

    private void dfs(int index, int lastPick, int[] nums) {
        if (index == nums.length) {
            if (list.size() > 1) {
                ans.add(new ArrayList<Integer>(list));
            }
            return;
        }
        /*
        对于两个相等的元素，例如[4,7,7]，需要避免选出[4,7]和[4,7]。对于这两个7，情况有都选，都不选，选第一个不选第二个，选第二个不选第一个共4种情况，
        后两种是等价的，需要去重，因此，当当前的元素等于上一次选择的元素时，只考虑选择当前元素的情况而不考虑不选择当前元素的情况。
        */
        if (nums[index] == lastPick) { // 只考虑选择nums[index]的情况而不考虑不选择nums[index]的情况以去重
            list.add(nums[index]);
            dfs(index + 1, nums[index], nums);
            list.remove(list.size() - 1);
        }
        else {
            if (nums[index] > lastPick) {
                list.add(nums[index]);
                dfs(index + 1, nums[index], nums);
                list.remove(list.size() - 1);
            }
            dfs(index + 1, lastPick, nums);
        }
    }

    public static void main(String[] args) {
        Solution491 solu = new Solution491();
        System.out.println(solu.findSubsequences(new int[]{4,6,7,7}));
        Solution491 solu2 = new Solution491();
        System.out.println(solu2.findSubsequences_implementation2(new int[]{4,6,7,7}));
    }
}