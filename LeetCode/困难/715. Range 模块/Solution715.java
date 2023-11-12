/*
url: https://leetcode.cn/problems/range-module/?envType=daily-question&envId=2023-11-12
相关: LeetCode56. 合并区间, LeetCode57. 插入区间
LeetCode题解: https://leetcode.cn/problems/range-module/solutions/1608992/range-mo-kuai-by-leetcode-solution-4utf/
              https://leetcode.cn/problems/range-module/solutions/1612952/by-ac_oier-i4sw/
标签: 区间合并, 区间删除, 二分查找, 有序集合, TreeMap, 线段树
*/

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/* 用LeetCode57. 插入区间的代码 + 二分查找写了出来。相关题解中有提到用有序集合和线段树的，这题应该是适合用有序集合让区间左端点自动按序的，
我没用有序集合所以removeRange()最后要排序一下，不管了。
*/
public class Solution715 {
    List<int[]> intervals;

    // 粘贴到LeetCode上把这个方法名改为RangeModule
    public Solution715() {
        this.intervals = new ArrayList<>();
    }
    
    public void addRange(int left, int right) {
        List<int[]> mergedIntervals = new ArrayList<>();
        int i = 0;
        while (i < intervals.size() && intervals.get(i)[1] < left) {
            mergedIntervals.add(intervals.get(i));
            i++;
        }
        while (i < intervals.size() && intervals.get(i)[0] <= right) {
            left = Math.min(left, intervals.get(i)[0]);
            right = Math.max(right, intervals.get(i)[1]);
            i++;
        }
        mergedIntervals.add(new int[]{left, right});
        while (i < intervals.size()) {
            mergedIntervals.add(intervals.get(i));
            i++;
        }
        this.intervals = mergedIntervals;
    }
    
    public boolean queryRange(int left, int right) {
        // 二分查找，搜索最后一个左端点<=left的区间
        int lo = 0, hi = intervals.size() - 1;
        // 闭区间写法，搜索[0, intervals.size() - 1]
        while (lo <= hi) {
            int mi = (lo + hi) / 2;
            if (intervals.get(mi)[0] <= left) {
                lo = mi + 1;
            }
            else hi = mi - 1;
        }
        if (lo - 1 == -1) return false;
        if (intervals.get(lo - 1)[0] <= left && intervals.get(lo - 1)[1] >= right) return true;
        return false;
    }
    
    public void removeRange(int left, int right) {
        for (int i = 0; i < intervals.size(); i++) {
            int[] interval = intervals.get(i);
            if (interval[1] <= left || interval[0] >= right) { // 无交集
                continue;
            }
            else if (interval[0] <= left && interval[1] >= right) { // (left, right)在某个区间内部，将interval拆成2个区间
                int[] sub1 = new int[]{interval[0], left};
                int[] sub2 = new int[]{right, interval[1]};
                if (!(sub1[0] == sub1[1])) intervals.add(sub1);
                if (!(sub2[0] == sub2[1])) intervals.add(sub2);
                intervals.remove(i);
                i--;
                break; // 后续区间不会再与(left, right)有交集，无需判断
            }
            else if (left < interval[0] && right > interval[1]) { // (left, right)包含interval
                intervals.remove(i);
                i--;
            }
            else { // 错开相交
                if (left >= interval[0]) {
                    interval[1] = left;
                }
                else {
                    interval[0] = right;
                }
            }
        }
        Collections.sort(intervals, (x, y) -> x[0] - y[0]);
    }

    public static void main(String[] args) {
        Solution715 solu = new Solution715();
        /* solu.addRange(10, 20);
        solu.removeRange(14, 16);
        System.out.println(solu.queryRange(10, 14));
        System.out.println(solu.queryRange(13, 15));
        System.out.println(solu.queryRange(16, 17)); */

        solu.addRange(44, 53);
        solu.addRange(69, 89);
        solu.removeRange(86, 91);
        solu.addRange(87, 94);
        solu.removeRange(34, 52);
        solu.addRange(1, 59);
        solu.removeRange(62, 96);
        solu.removeRange(34, 83);
        System.out.println(solu.queryRange(1, 13));
    }
}
