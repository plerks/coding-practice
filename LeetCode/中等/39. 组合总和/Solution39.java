/*
url: https://leetcode.cn/problems/combination-sum/
相关: https://leetcode.cn/problems/number-of-ways-to-buy-pens-and-pencils/
标签: 选数，凑值
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution39 {
    public List<List<Integer>> ans = new ArrayList<>();

    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < candidates.length; i++) {
            // 用新函数（调整递归函数的参数）来递归
            myCombinationSum(candidates, list, i, target);
        }
        return this.ans;
    }

    private void myCombinationSum(int[] candidates, List<Integer> list, int position, int target) {
        // 加上当前位置的数
        list.add(candidates[position]);
        target -= candidates[position];
        if (target < 0) {
            // 哪个栈帧add的，自己负责remove
            list.remove(list.size() - 1);
            // target += candidates[position]; 不需要把target加回来，传的是值进来，这栈帧马上就结束了
            return;
        }
        if (target == 0) {
            this.ans.add(new ArrayList<>(list));
            list.remove(list.size() - 1);
            // target += candidates[position];
            return;
        }
        // 子问题是在[position, ..]中找和为新target的解法，包含position位置是因为一个数可以反复用，不包含position左侧是因为例如[3, 5]和[5,3]会重复
        for (int i = position; i < candidates.length; i++) {
            myCombinationSum(candidates, list, i, target);
            // 这里可以剪枝，如果candidate排好序了，例如[2,2,2,2]命中后，后面的[2,2,2,3]之类的就不需要再尝试，见myCombinationSum_implementation2
        }
        list.remove(list.size() - 1);
        // target += candidates[position];
    }

    public List<List<Integer>> combinationSum_implementation2(int[] candidates, int target) {
        List<Integer> list = new ArrayList<>();
        Arrays.sort(candidates);
        for (int i = 0; i < candidates.length; i++) {
            // 用新函数（调整递归函数的参数）来递归
            myCombinationSum_implementation2(candidates, list, i, target);
        }
        return this.ans;
    }

    private int myCombinationSum_implementation2(int[] candidates, List<Integer> list, int position, int target) {
        list.add(candidates[position]);
        target -= candidates[position];
        if (target < 0) {
            list.remove(list.size() - 1);
            return target;
        }
        if (target == 0) {
            this.ans.add(new ArrayList<>(list));
            list.remove(list.size() - 1);
            return target;
        }
        for (int i = position; i < candidates.length; i++) {
            int ret = myCombinationSum_implementation2(candidates, list, i, target);
            if (ret < 0) break;
        }
        list.remove(list.size() - 1);
        return target;
    }

    public static void main(String[] args) {
        Solution39 solu = new Solution39();
        System.out.println(solu.combinationSum(new int[]{2,3,6,7}, 7));
        Solution39 solu2 = new Solution39();
        System.out.println(solu2.combinationSum_implementation2(new int[]{2,3,6,7}, 7));
    }
}