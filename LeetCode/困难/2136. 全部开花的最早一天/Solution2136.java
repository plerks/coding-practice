/*
url: https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/?envType=daily-question&envId=2023-09-30
LeetCode参考: https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/solutions/1202113/quan-bu-kai-hua-de-zui-zao-yi-tian-by-le-ocxg/
              https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/solutions/1200254/tan-xin-ji-qi-zheng-ming-by-endlesscheng-hfwe/
相关: LeetCode1402. 做菜顺序
标签: 贪心, 局部调整法
*/

import java.util.Arrays;

public class Solution2136 {
    public int earliestFullBloom(int[] plantTime, int[] growTime) {
        int n = plantTime.length;
        Integer[] ids = new Integer[n];
        for (int i = 0; i < n; i++) {
            ids[i] = i;
        }
        Arrays.sort(ids, (x, y) -> {
            return growTime[y] - growTime[x];
        });
        int ans = 0;
        int prev = 0;
        for (int id : ids) {
            ans = Math.max(ans, prev + plantTime[id] + growTime[id]);
            prev += plantTime[id];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2136 solu = new Solution2136();
        System.out.println(solu.earliestFullBloom(new int[]{1,4,3}, new int[]{2,3,1}));
    }
}