/*
url: https://leetcode.cn/problems/subsets/
LeetCode题解: https://leetcode.cn/problems/subsets/solutions/2367622/problem-78-zi-ji-by-alworn-skns/
              https://leetcode.cn/problems/TVdhkn/solutions/2329301/suo-you-zi-ji-by-relaxed-7eavittpjh-jem4/
              https://leetcode.cn/problems/TVdhkn/solutions/2288876/jing-dian-de-zi-ji-shu-wen-ti-by-nice-sa-5f3t/
标签: 求幂集, 幂集递归
*/

import java.util.*;

public class Solution78 {
    List<List<Integer>> ans = new ArrayList<>();
    HashSet<Integer> set = new HashSet<>(); // 用数组好像也行

    public List<List<Integer>> subsets(int[] nums) {
        mySubsets(nums, 0);
        return ans;
    }

    // 调用树是nums.length - 1叉树
    private void mySubsets(int[] nums, int index) {
        ans.add(new ArrayList<>(set));
        for (int i = index; i < nums.length; i++) {
            set.add(nums[i]);
            mySubsets(nums, i + 1);
            set.remove(nums[i]);
        }
    }

    public List<List<Integer>> subsets_implementation2(int[] nums) {
        mySubsets_implementation2(nums, 0);
        return ans;
    }

    // 调用树是二分的
    private void mySubsets_implementation2(int[] nums, int index) {
        // 每个元素都尝试了是否加入
        if (index == nums.length) {
            ans.add(new ArrayList<>(set));
        }
        else {
            mySubsets_implementation2(nums, index + 1); // nums[i]不加入
            set.add(nums[index]);
            mySubsets_implementation2(nums, index + 1); // nums[i]加入
            set.remove(nums[index]);
        }
    }

    // 不递归的写法
    public List<List<Integer>> subsets_implementation3(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        ans.add(new ArrayList<>());
        for (int i = 0; i < nums.length; i++) {
            int size = ans.size();
            for (int j = 0; j < size; j++) {
                List<Integer> list = new ArrayList<>(ans.get(j));
                list.add(nums[i]);
                ans.add(list);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution78 solu = new Solution78();
        System.out.println(solu.subsets(new int[]{1,2,3}));
        solu.ans = new ArrayList<>();
        solu.set = new HashSet<>();
        System.out.println(solu.subsets_implementation2(new int[]{1,2,3}));
        System.out.println(solu.subsets_implementation3(new int[]{1,2,3}));
    }
}