/*
url: https://leetcode.cn/problems/minimum-string-length-after-removing-substrings/description/?envType=daily-question&envId=2024-01-10
LeetCode参考: https://leetcode.cn/problems/minimum-string-length-after-removing-substrings/solutions/2278343/liang-chong-suan-fa-bao-li-ti-huan-zhan-vto0o/
相关: LeetCode20. 有效的括号, LeetCode2645. 构造有效字符串的最少插入数
标签: 栈, 括号匹配
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution2696 {
    // 超时的递归办法
    public int minLength_exceedTimeLimit(String s) {
        int ans = s.length();
        for (int i = 0; i < s.length() - 1; i++) {
            if ((s.charAt(i) == 'A' && s.charAt(i + 1) == 'B') || (s.charAt(i) == 'C' && s.charAt(i + 1) == 'D')) {
                ans = Math.min(ans, minLength_exceedTimeLimit(s.substring(0, i) + s.substring(i + 2)));
            }
        }
        return ans;
    }

    // 参考LeetCode的题解，暴力法，但不超时
    public int minLength(String s) {
        while (s.contains("AB") || s.contains("CD")) {
            s = s.replace("AB", "").replace("CD", "");
        }
        return s.length();
    }

    // 参考LeetCode的题解，用一个栈，有点类似括号匹配
    public int minLength_implementation2(String s) {
        Deque<Character> stack = new LinkedList<>();
        for (int i = 0; i < s.length(); i++) {
            if (!stack.isEmpty() && ((stack.peek() == 'A' && s.charAt(i) == 'B') || (stack.peek() == 'C' && s.charAt(i) == 'D'))) {
                stack.pop();
            }
            else stack.push(s.charAt(i));
        }
        return stack.size();
    }

    public static void main(String[] args) {
        Solution2696 solu = new Solution2696();
        System.out.println(solu.minLength("EJCACACCABDDBDBDACDBCACCDDBDAACDBBWTCCDDM"));
        System.out.println(solu.minLength_implementation2("EJCACACCABDDBDBDACDBCACCDDBDAACDBBWTCCDDM"));
    }
}
