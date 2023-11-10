/*
url: https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/?envType=daily-question&envId=2023-11-10
LeetCode参考: https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/solutions/2477429/zhou-yu-he-yao-shui-de-cheng-gong-dui-sh-a22z/
标签: 二分查找, 双指针, 标号数组排序
相关: 典型问题/有序范围内的二分查找, 典型问题/使用标号数组排序
*/

import java.util.Arrays;

public class Solution2300 {
    public int[] successfulPairs(int[] spells, int[] potions, long success) {
        int[] ans = new int[spells.length];
        Arrays.sort(potions);
        for (int i = 0; i < spells.length; i++) {
            int left = 0, right = potions.length - 1;
            // spells[i] * potions[mid] >= success满足从否到是，搜索第一个是的位置，即最后一个否的位置+1
            // 闭区间写法
            while (left <= right) {
                int mid = (left + right) / 2;
                if ((long)spells[i] * potions[mid] < success) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
                // 此时left为第一个spells[i] * potions[mid] >= success的位置
                ans[i] = potions.length - left;
            }
        }
        return ans;
    }

    // [LeetCode官方题解](https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/solutions/2477429/zhou-yu-he-yao-shui-de-cheng-gong-dui-sh-a22z/)提供了一种双指针的解法，不会比二分查找更优，但是也值得一看
    public int[] successfulPairs_implementation2(int[] spells, int[] potions, long success) {
        int[] ans = new int[spells.length];
        Integer[] idx = new Integer[spells.length];
        for (int i = 0; i < idx.length; i++) {
            idx[i] = i;
        }
        // 用标号数组，让spell升序，并且能靠idx[i]找到原来位置
        Arrays.sort(idx, (x, y) -> {
            return spells[x] - spells[y];
        });
        Arrays.sort(potions);
        // reverse potions, 让potions降序
        for (int i = 0; potions.length - 1 - i > i; i++) {
            int temp = potions[i];
            potions[i] = potions[potions.length - 1 - i];
            potions[potions.length - 1 - i] = temp;
        }
        // 这里是idx按spells升序，potions降序，反过来应该也可以实现，应该就是变成(j, potions.length - 1]的药水都够大，j只减不增
        for (int i = 0, j = 0; i < idx.length; i++) {
            while (j < potions.length && (long)spells[idx[i]] * potions[j] >= success) {
                j++;
            }
            // [0, j)的药水都够大能使得乘积>=success，下一个spell[idx[i]]会更大，因此j只增不减，不用回头
            ans[idx[i]] = j;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2300 solu = new Solution2300();
        System.out.println(Arrays.toString(solu.successfulPairs(new int[]{5,1,3}, new int[]{1,2,3,4,5}, 7)));
        System.out.println(Arrays.toString(solu.successfulPairs_implementation2(new int[]{5,1,3}, new int[]{1,2,3,4,5}, 7)));
    }
}
