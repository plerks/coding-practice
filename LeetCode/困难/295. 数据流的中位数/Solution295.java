/*
url: https://leetcode.cn/problems/find-median-from-data-stream/description/
LeetCode参考: https://leetcode.cn/problems/find-median-from-data-stream/solutions/961062/shu-ju-liu-de-zhong-wei-shu-by-leetcode-ktkst/
相关: LeetCodeLCP 24. 数字游戏, 典型问题/k选取, LeetCode215. 数组中的第K个最大元素
标签: 双优先队列, 中位数, 求流的中位数
*/

import java.util.*;

public class Solution295 {
    /* 用双优先队列来在遍历流的过程中求中位数，lower保存的元素<=upper的元素，
    `LeetCodeLCP 24. 数字游戏`中是让lower元素数量比upper大1或相等，这里尝试另外一种，
    让所含元素数量关系保持n_lower<=n_upper<=n_lower+1，即upper元素数量比lower大1或相等。
    */
    PriorityQueue<Integer> lower;
    PriorityQueue<Integer> upper;

    // 粘贴到LeetCode上把这个方法改为MedianFinder()
    public Solution295() {
        lower = new PriorityQueue<>((x, y) -> y - x);
        upper = new PriorityQueue<>((x, y) -> x - y);
    }
    
    public void addNum(int num) {
        // 优先往upper里填
        if (upper.isEmpty() || num >= upper.peek()) {
            upper.offer(num);
        }
        else {
            lower.offer(num);
        }
        if (lower.size() == upper.size() + 1) {
            upper.offer(lower.poll());
        }
        else if (upper.size() == lower.size() + 2) {
            lower.offer(upper.poll());
        }
    }
    
    public double findMedian() {
        if (lower.size() == upper.size()) {
            return ((double)lower.peek() + upper.peek()) / 2;
        }
        else return upper.peek();
    }

    public static void main(String[] args) {
        Solution295 solu = new Solution295();
        solu.addNum(1);
        solu.addNum(2);
        System.out.println(solu.findMedian());
        solu.addNum(3);
        System.out.println(solu.findMedian());
    }
}
