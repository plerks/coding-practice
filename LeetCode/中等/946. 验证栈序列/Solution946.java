/*
url: https://leetcode.cn/problems/validate-stack-sequences/
LeetCode参考: https://leetcode.cn/problems/validate-stack-sequences/solutions/1785639/yan-zheng-zhan-xu-lie-by-leetcode-soluti-cql0/
标签: 验证栈混洗, 验证栈序列
*/

import java.util.*;

class Solution946 {
    // 我的写法
    public boolean validateStackSequences(int[] pushed, int[] popped) {
        Deque<Integer> stack = new LinkedList<>();
        int index1 = 0, index2 = 0;
        int n = popped.length;
        // popped.length == pushed.length
        // 模拟push, pop过程，pushed未用完之前，根据栈顶是否已经是poped第一个待匹配元素，决定是push还是pop
        while (index1 < n) {
            if (!stack.isEmpty() && stack.peek() == popped[index2]) {
                stack.pop();
                index2++;
            }
            else {
                stack.push(pushed[index1++]);
            }
        }
        while (!stack.isEmpty() && stack.peek() == popped[index2]) {
            stack.pop();
            index2++;
        }
        return stack.isEmpty();
    }

    // 官方题解的写法，更清晰
    public boolean validateStackSequences_implementation2(int[] pushed, int[] popped) {
        Deque<Integer> stack = new LinkedList<>();
        int n = popped.length;
        for (int i = 0, j = 0; i < n; i++) {
            stack.push(pushed[i]);
            while (!stack.isEmpty() && stack.peek() == popped[j]) {
                stack.pop();
                j++;
            }
        }
        return stack.isEmpty();
    }

    public static void main(String[] args) {
        Solution946 solu = new Solution946();
        System.out.println(solu.validateStackSequences(new int[]{1,2,3,4,5}, new int[]{4,5,3,2,1}));
        System.out.println(solu.validateStackSequences_implementation2(new int[]{1,2,3,4,5}, new int[]{4,5,3,2,1}));
    }
}