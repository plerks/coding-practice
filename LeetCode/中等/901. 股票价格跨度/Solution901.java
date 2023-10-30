/*
url: https://leetcode.cn/problems/online-stock-span/?envType=daily-question&envId=2023-10-07
标签: 单调栈, 用单调栈寻找左侧第一个比当前元素大的元素
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution901 {

    public Deque<int[]> stack;
    int index;

    // 粘贴到LeetCode上要把这个方法名改为StockSpanner
    public Solution901() {
        stack = new LinkedList<>();
        index = -1;
    }
    
    public int next(int price) {
        /* 用单调栈求出上一个大于price的索引，小于price的元素直接出，若后续某个值小于price
        则其所求位置就是price的位置，否则小于price的元素也会小于那个值，小于price的元素直接出不会影响
        */
        index++; // price这个元素的位置
        while (!stack.isEmpty() && stack.peek()[0] <= price) {
            stack.pop();
        }
        int lastBiggerIndex = stack.isEmpty() ? -1 : stack.peek()[1];
        stack.push(new int[]{price, index});
        return index - lastBiggerIndex;
    }

    public static void main(String[] args) {
        Solution901 solu = new Solution901();
        System.out.println(solu.next(100));
        System.out.println(solu.next(80));
        System.out.println(solu.next(60));
        System.out.println(solu.next(70));
        System.out.println(solu.next(60));
        System.out.println(solu.next(75));
        System.out.println(solu.next(85));
    }
}