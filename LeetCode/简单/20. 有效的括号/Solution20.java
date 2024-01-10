/*
url: https://leetcode.cn/problems/valid-parentheses/description/
相关: LeetCode2696. 删除子串后的字符串最小长度, LeetCode2645. 构造有效字符串的最少插入数
标签: 栈, 括号匹配
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution20 {
    public boolean isValid(String s) {
        Deque<Character> stack = new LinkedList<>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            }
            else { // 右括号
                if (c == ')' && (stack.isEmpty() || stack.peek() != '(')) return false;
                if (c == ']' && (stack.isEmpty() || stack.peek() != '[')) return false;
                if (c == '}' && (stack.isEmpty() || stack.peek() != '{')) return false;
                stack.pop();
            }
        }
        return stack.isEmpty() ? true : false;
    }

    public static void main(String[] args) {
        Solution20 solu = new Solution20();
        System.out.println(solu.isValid("()[]{}"));
    }
}
