/*
url: https://leetcode.cn/problems/verify-preorder-serialization-of-a-binary-tree/description/?envType=daily-question&envId=2024-03-31
LeetCode参考: https://leetcode.cn/problems/verify-preorder-serialization-of-a-binary-tree/solutions/650583/yan-zheng-er-cha-shu-de-qian-xu-xu-lie-h-jghn/
相关: LeetCode105. 从前序与中序遍历序列构造二叉树, LeetCode106. 从中序与后序遍历序列构造二叉树, LeetCodeLCR 152. 验证二叉搜索树的后序遍历序列
标签: 前序遍历, 先序遍历
*/
import java.util.*;

/* 这题如果是检验序列是否是后序遍历的序列化，应该是将后序遍历反过来看是根-右-左，然后类似的做法。LeetCode上没找到类似的题，只找到
一道`LeetCodeLCR 152. 验证二叉搜索树的后序遍历序列`是验证序列是否是二叉搜索树的后序遍历。 */
public class Solution331 {
    // 我的解法
    public boolean isValidSerialization(String preorder) {
        if (preorder.charAt(0) == '#') return preorder.length() == 1;
        int[] node = new int[]{-1, -1}; // 用-1,-1代表节点的左右子树都还没被确认过(有节点/为空)
        Deque<int[]> stack = new LinkedList<>();
        stack.push(node);
        int i = 0;
        while (i < preorder.length() && preorder.charAt(i) != ',') i++;
        i++; // i指到下一个数
        for (; i < preorder.length();) {
            char c = preorder.charAt(i);
            if (stack.isEmpty()) return false;
            if (c == '#') {
                if (stack.peek()[0] == -1) stack.peek()[0] = 1;
                else if (stack.peek()[1] == -1) {
                    stack.peek()[1] = 1;
                    stack.pop();
                }
                // else return false; // 这里不需要else return false;，不会有这种情况
            }
            else {
                int[] child = new int[]{-1, -1};
                if (stack.peek()[0] == -1) {
                    stack.peek()[0] = 1;
                    stack.push(child);
                }
                else if (stack.peek()[1] == -1) {
                    stack.peek()[1] = 1;
                    stack.pop();
                    stack.push(child);
                }
                // else return false; // 这里不需要else return false;，不会有这种情况
            }
            while (i < preorder.length() && preorder.charAt(i) != ',') i++;
            i++;
        }
        return stack.isEmpty();
    }

    // 官方题解解法一，用“槽位”的概念表示当前二叉树中正在等待被节点填充的位置。填充空节点为儿子槽位数-1；填充非空节点为儿子槽位数-1，这个非空节点+2槽位
    public boolean isValidSerialization_implementation2(String preorder) {
        int n = preorder.length();
        int i = 0;
        Deque<Integer> stack = new LinkedList<>(); // 用来记录槽位数量
        stack.push(1); // 最开始为空，可以充一个根节点
        while (i < n) {
            if (stack.isEmpty()) return false;
            if (preorder.charAt(i) == '#') {
                int count = stack.pop() - 1;
                if (count > 0) { // 槽位没用完，不弹出
                    stack.push(count);
                }
                i++;
            }
            else if (preorder.charAt(i) == ',') {
                i++;
            }
            else {
                while (i < n && preorder.charAt(i) != ',') i++;
                int count = stack.pop() - 1;
                if (count > 0) { // 槽位没用完，不弹出
                    stack.push(count);
                }
                stack.push(2); // 一个新的非空节点有2个槽位
            }
        }
        return stack.isEmpty();
    }

    // 官方题解解法二，不需要用栈，只需要记录剩余槽位数量即可
    public boolean isValidSerialization_implementation3(String preorder) {
        int n = preorder.length();
        int i = 0;
        int count = 1; // 槽位数量，最开始的1是给根的
        while (i < n) {
            if (count == 0) return false;
            if (preorder.charAt(i) == '#') {
                count--;
                i++;
            }
            else if (preorder.charAt(i) == ',') {
                i++;
            }
            else {
                while (i < n && preorder.charAt(i) != ',') i++;
                count--;
                count += 2;
            }
        }
        return count == 0;
    }

    public static void main(String[] args) {
        Solution331 solu = new Solution331();
        System.out.println(solu.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
        System.out.println(solu.isValidSerialization("1,#"));
        System.out.println(solu.isValidSerialization("9,#,#,1"));
        System.out.println(solu.isValidSerialization("#"));
        System.out.println(solu.isValidSerialization("#,#,#"));
        System.out.println(solu.isValidSerialization("9,#,92,#,#"));
        System.out.println(solu.isValidSerialization("92,3,4,#,#,1,#,#,2,#,6,#,#"));
        System.out.println(solu.isValidSerialization_implementation2("9,3,4,#,#,1,#,#,2,#,6,#,#"));
        System.out.println(solu.isValidSerialization_implementation3("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    }
}
