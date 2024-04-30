/*
url: https://leetcode.cn/problems/count-integers-in-intervals/description/
LeetCode参考: https://leetcode.cn/problems/count-integers-in-intervals/solutions/2566065/tong-ji-qu-jian-zhong-de-zheng-shu-shu-m-jkey/
              https://leetcode.cn/problems/count-integers-in-intervals/solutions/1495396/by-endlesscheng-clk2/
相关: LeetCode57. 插入区间, LeetCode56. 合并区间
标签: 区间, 区间合并, 有序集合, 平衡二叉搜索树, 红黑树, 线段树
*/

import java.util.*;

class CountIntervals {
    int count;
    TreeMap<Integer, Integer> map = new TreeMap<>();

    public CountIntervals() {

    }
    
    public void add(int left, int right) {
        Map.Entry<Integer, Integer> entry = map.floorEntry(right);
        while (entry != null && entry.getValue() >= left) {
            left = Math.min(left, entry.getKey());
            right = Math.max(right, entry.getValue());
            count -= entry.getValue() - entry.getKey() + 1;
            map.remove(entry.getKey());
            entry = map.floorEntry(right);
        }
        count += right - left + 1;
        map.put(left, right);
    }
    
    public int count() {
        return count;
    }

    public static void main(String[] args) {
        CountIntervals solu = new CountIntervals();
        solu.add(2, 3);
        solu.add(7, 10);
        solu.add(5, 8);
        System.out.println(solu.count());
    }
}