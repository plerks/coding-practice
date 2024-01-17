/*
url: https://leetcode.cn/problems/removing-minimum-number-of-magic-beans/description/?envType=daily-question&envId=2024-01-18
LeetCode参考: https://leetcode.cn/problems/removing-minimum-number-of-magic-beans/solutions/1270306/na-chu-zui-shao-shu-mu-de-mo-fa-dou-by-l-dhsl/
标签: 前缀和
*/

import java.util.Arrays;

public class Solution2171 {
    public long minimumRemoval(int[] beans) {
        Arrays.sort(beans);
        long ans = Long.MAX_VALUE;
        int n = beans.length;
        long[] prefixSum = new long[n];
        for (int i = 0; i < n; i++) {
            prefixSum[i] = (i == 0) ? beans[0] : (prefixSum[i - 1] + beans[i]);
        }
        for (int i = 0; i < n; i++) { // 枚举最终的相等豆子数值
            long num = 0;
            num += prefixSum[i] - beans[i]; // 前面小的拿为0
            num += prefixSum[n - 1] - prefixSum[i] - (n - 1 - i) * (long)(beans[i]); // 后面的拿为beans[i]
            ans = Math.min(ans, num);
        }
        return ans;
    }

    // 参考题解的做法，不用算前缀和
    public long minimumRemoval_implementation2(int[] beans) {
        Arrays.sort(beans);
        int n = beans.length;
        long total = 0;
        for (int i = 0; i < n; i++) {
            total += beans[i];
        }
        long ans = total; // total为全拿为0所需拿的个数
        for (int i = 0; i < n; i++) { // 枚举最终的相等豆子数值
            ans = Math.min(ans, total - (long)beans[i] * (n - i)); // 相比每个拿为0，每个拿为beans[i]所少拿的个数为beans[i] * (n - i)
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2171 solu = new Solution2171();
        System.out.println(solu.minimumRemoval(new int[]{2,10,3,2}));
        System.out.println(solu.minimumRemoval_implementation2(new int[]{2,10,3,2}));
    }
}
