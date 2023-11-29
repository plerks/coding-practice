/*
url: https://leetcode.cn/problems/smallest-number-in-infinite-set/?envType=daily-question&envId=2023-11-29
标签: TreeSet
*/

import java.util.*;

public class Solution2336 {
    /* int infiniteIntervalLeft; // 无穷区间的左端点
    Set<Integer> set;
    PriorityQueue<Integer> q;

    // 粘贴到LeetCode上把这个方法改名为SmallestInfiniteSet()
    public Solution2336() {
        this.infiniteIntervalLeft = 1;
        this.set = new HashSet<>();
        this.q = new PriorityQueue<>();
    }
    
    public int popSmallest() {
        if (set.isEmpty()) {
            infiniteIntervalLeft++;
            return infiniteIntervalLeft - 1;
        }
        else {
            int val = q.poll();
            set.remove(val);
            return val;
        }
    }
    
    public void addBack(int num) {
        if (num >= infiniteIntervalLeft) return;
        if (set.contains(num)) return;
        set.add(num);
        q.add(num);
    } */

    // 用TreeSet的写法

    int infiniteIntervalLeft;
    TreeSet<Integer> set;

    // 粘贴到LeetCode上把这个方法改名为SmallestInfiniteSet()
    public Solution2336() {
        this.infiniteIntervalLeft = 1;
        this.set = new TreeSet<>();
    }
    
    public int popSmallest() {
        if (set.isEmpty()) {
            infiniteIntervalLeft++;
            return infiniteIntervalLeft - 1;
        }
        else {
            return set.pollFirst();
        }
    }
    
    public void addBack(int num) {
        if (num >= infiniteIntervalLeft) return;
        if (set.contains(num)) return;
        set.add(num);
    }

    public static void main(String[] args) {
    }
}
