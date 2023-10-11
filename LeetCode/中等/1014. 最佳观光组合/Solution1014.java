/*
url: https://leetcode.cn/problems/best-sightseeing-pair/
LeetCode参考: https://leetcode.cn/problems/best-sightseeing-pair/solutions/291380/zui-jia-guan-guang-zu-he-by-leetcode-solution/
标签: 公式变换技巧
*/

public class Solution1014 {
    public int maxScoreSightseeingPair(int[] values) {
        // values[i] + values[j] + i - j变换成(value[i] + i) + (value[j] - j)，从前往后遍历，前一项可以用max值记录目前的最大值，后一项直接算
        int ans = 0, max = values[0] + 0;
        for (int i = 1; i < values.length; i++) {
            ans = Math.max(ans, max + values[i] - i);
            max = Math.max(max, values[i] + i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1014 solu = new Solution1014();
        System.out.println(solu.maxScoreSightseeingPair(new int[]{8,1,5,2,6}));
    }
}
