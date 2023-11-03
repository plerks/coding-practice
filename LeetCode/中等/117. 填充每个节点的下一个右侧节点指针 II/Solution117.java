/*
url: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/?envType=daily-question&envId=2023-11-03
LeetCode参考: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/solutions/429828/tian-chong-mei-ge-jie-dian-de-xia-yi-ge-you-ce-15/
标签: 层序遍历, 层序遍历区分层节点
*/

import java.util.*;

public class Solution117 {
    // 需要使用一个队列，无法达到题目要求的空间复杂度O(1)
    public Node connect(Node root) {
        if (root == null) return null;
        Deque<Node> q = new LinkedList<>();
        q.offer(root);
        while (!q.isEmpty()) {
            int n = q.size(); // n为这一层的节点数量，这样可以区分每一层的节点
            for (int i = 0; i < n; i++) {
                Node node = q.poll();
                if (node.left != null) q.offer(node.left);
                if (node.right != null) q.offer(node.right);
                if (i != n - 1) node.next = q.peek();
            }
        }
        return root;
    }

    // 空间复杂度O(1)的实现方式，在遍历某一层的节点时(next关系已由上一层构建)，将下一层的节点的next连接起来
    public Node connect_implementation2(Node root) {
        if (root == null) return null;
        Node start = root, nextStart;
        Node last;
        while (start != null) {
            nextStart = null; // nextStart为下层的第一个节点
            last = null; // 这一层上一个碰到的节点
            for (Node p = start; p != null; p = p.next) {
                if (p.left != null) {
                    if (nextStart == null) nextStart = p.left;
                    if (last != null) {
                        last.next = p.left;
                    }
                    last = p.left;
                }
                if (p.right != null) {
                    if (nextStart == null) nextStart = p.right;
                    if (last != null) {
                        last.next = p.right;
                    }
                    last = p.right;
                }
            }
            start = nextStart;
        }
        return root;
    }

    public static void main(String[] args) {
    }
}

class Node {
    public int val;
    public Node left;
    public Node right;
    public Node next;

    public Node() {}
    
    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, Node _left, Node _right, Node _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
}