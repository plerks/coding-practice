/*
url: https://leetcode.cn/problems/minimum-additions-to-make-valid-string/description/?envType=daily-question&envId=2024-01-11
LeetCode参考: https://leetcode.cn/problems/minimum-additions-to-make-valid-string/solutions/2229526/kao-lu-xiang-lin-zi-mu-pythonjavacgo-by-m9yrc/
相关: LeetCode2696. 删除子串后的字符串最小长度, LeetCode20. 有效的括号
标签: 栈, 括号匹配
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution2645 {
    // 我的用栈模拟的解法，有点像昨天的LeetCode2696. 删除子串后的字符串最小长度的栈用法，性能不佳。参考题解的两种解法都很巧妙
    public int addMinimum(String word) {
        Deque<Character> stack = new LinkedList<>();
        int ans = 0;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c == 'a') { // a期望遇到c或空栈，否则要为前面补
                if (!stack.isEmpty() && stack.peek() != 'c') {
                    ans += 'c' - stack.peek(); // peek为a补bc, 为b补c
                }
                stack.push('a');
            }
            else if (c == 'b') {
                if (stack.isEmpty() || stack.peek() != 'a') {
                    ans += (stack.isEmpty() || stack.peek() == 'c') ? 1 : 2; // peek为空补a,为b补ca, 为c补a
                }
                stack.push('b');
            }
            else { // c == 'c'
                if (stack.isEmpty() || stack.peek() != 'b') {
                    ans += (stack.isEmpty() || stack.peek() == 'c') ? 2 : 1; // peek为空补ab,为a补b, 为c补ab
                }
                stack.push('c');
            }
        }
        ans += 'c' - stack.peek(); // 最后补尾巴
        return ans;
    }

    // 参考题解解法一，考虑相邻字母
    public int addMinimum_implementation2(String word) {
        char[] s = word.toCharArray();
        int ans = 0;
        ans += (s[0] - 'a') + ('c' - s[s.length - 1]); // 开头和末尾的补充
        for (int i = 1; i < s.length; i++) {
            // 对相邻的s[i - 1]和s[i]，使得有效需要插入s[i] - s[i - 1] - 1个字符，+3再%3是为了使其为正
            // 若"s[i - 1],s[i]"合a-b-c的循环顺序，无需插入字符，若不合法，需要插入字符，且插入是在中间插入使符合a-b-c的循环顺序，末尾仍是s[i]
            ans += (s[i] - s[i - 1] - 1 + 3) % 3;
        }
        return ans;
    }

    // 参考题解解法二，考虑"abc"的个数
    public int addMinimum_implementation3(String word) {
        // 最终得到的有效字符串的"abc"个数为t，则需要插入的字符数为3t-word.length，只需求出t
        char[] s = word.toCharArray();
        int edge = 0;
        for (int i = 1; i < s.length; i++) {
            if (s[i] <= s[i - 1]) { // 说明s[i]属于一个新的"abc"
                edge++;
            }
        }
        // 有edge个边缘，则有edge + 1个"abc"片段，t = edge + 1
        return 3 * (edge + 1) - word.length();
    }

    public static void main(String[] args) {
        Solution2645 solu = new Solution2645();
        System.out.println(solu.addMinimum("aaaabb"));
        System.out.println(solu.addMinimum_implementation2("aaaabb"));
        System.out.println(solu.addMinimum_implementation3("aaaabb"));
    }
}
