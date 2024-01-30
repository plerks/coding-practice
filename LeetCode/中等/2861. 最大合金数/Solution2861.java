/*
url: https://leetcode.cn/problems/maximum-number-of-alloys/description/?envType=daily-question&envId=2024-01-27
标签: 二分查找
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution2861 {
    /* 原本以为有更巧妙的做法，但是题解也是二分。如果用模拟的方式做，可能能这样：如果目前的stock一份都做不了，补充到可做的最小套数，更新stock，继续循环；
    如果可以做，则做，更新stock，继续循环。
    这里容易想到二分的原因是对于生产数量n，很容易计算budget够不够，根据生产n需要的材料数量计算需要补充的材料数量即可，而且区间变化也符合单调性。
    */
    public int maxNumberOfAlloys(int n, int k, int budget, List<List<Integer>> composition, List<Integer> stock, List<Integer> cost) {
        int ans = 0;
        for (int i = 0; i < k; i++) {
            List<Integer> stockClone = new ArrayList<>(stock.size());
            for (int val : stock) stockClone.add(val);
            ans = Math.max(ans, binSearch(n, i, budget, composition, stockClone, cost));
        }
        return ans;
    }

    private int binSearch(int n, int machine, int budget, List<List<Integer>> composition, List<Integer> stock, List<Integer> cost) {
        long left = 0, right = 0; // 搜索能做的套数，区间从是到否变化，搜索最后一个是
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < stock.size(); i++) {
            min = Math.min(min, stock.get(i));
        }
        right = budget + min; // right初值为budget + min{stock[i]}
        List<Integer> comp = composition.get(machine);
        while (left <= right) {
            long mid = (left + right) >> 1;
            if (check(mid, budget, comp, stock, cost)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return (int)left - 1;
    }

    private boolean check(long num, int budget, List<Integer> comp, List<Integer> stock, List<Integer> cost) {
        long totalCost = 0;
        for (int i = 0; i < comp.size(); i++) {
            long supplyCount = num * comp.get(i) - stock.get(i);
            totalCost += (supplyCount >= 0 ? supplyCount : 0)  * (long)cost.get(i);
        }
        return totalCost <= budget;
    }

    public static void main(String[] args) {
        Solution2861 solu = new Solution2861();
        System.out.println(solu.maxNumberOfAlloys(3, 2, 15, Arrays.asList(Arrays.asList(1,1,1), Arrays.asList(1,1,10)), Arrays.asList(0,0,0), Arrays.asList(1,2,3)));
    }
}
