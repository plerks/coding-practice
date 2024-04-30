/*
url: https://leetcode.cn/problems/insert-interval/
LeetCode参考: https://leetcode.cn/problems/insert-interval/solutions/472435/shou-hua-tu-jie-57-cha-ru-qu-jian-fen-cheng-3ge-ji/
              https://leetcode.cn/problems/insert-interval/solutions/472151/cha-ru-qu-jian-by-leetcode-solution/
相关: LeetCode56. 合并区间, LeetCode715. Range 模块, LeetCode2580. 统计将重叠区间合并成组的方案数, LeetCode2276. 统计区间中的整数数目
标签: 区间合并
*/

import java.util.*;

public class Solution57 {
    // intervals已按区间左端点排序
    public int[][] insert(int[][] intervals, int[] newInterval) {
        List<int[]> mergedIntervals = new ArrayList<>();
        int i = 0;

        // newInterval相对已有的区间分为3个阶段，左边与newInterval无重叠的部分，中间有重叠的部分，右边无重叠的部分

        while (i < intervals.length && intervals[i][1] < newInterval[0]) {
            mergedIntervals.add(intervals[i]);
            i++;
        }

        while (i < intervals.length && !(intervals[i][0] > newInterval[1])) {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]); // newInterval记录了中间部分的合并结果
            i++;
        }
        mergedIntervals.add(newInterval);

        while (i < intervals.length) {
            mergedIntervals.add(intervals[i]);
            i++;
        }

        int[][] ans = new int[mergedIntervals.size()][2];
        for (int j = 0; j < ans.length; j++) {
            ans[j] = mergedIntervals.get(j);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution57 solu = new Solution57();
        System.out.println(Arrays.deepToString(solu.insert(new int[][]{{1,3},{6,9}}, new int[]{2,5})));
    }
}