/*
url: https://leetcode.cn/problems/n-ary-tree-level-order-traversal/description/?envType=daily-question&envId=2024-02-17
相关: LeetCode102. 二叉树的层序遍历, LeetCode107. 二叉树的层序遍历 II, LeetCode103. 二叉树的锯齿形层序遍历
标签: N叉树的层序遍历
*/

import java.util.*;

public class Solution429 {
    public List<List<Integer>> levelOrder(Node root) {
        Deque<Node> q = new LinkedList<>();
        List<List<Integer>> ans = new ArrayList<>();
        if (root != null) q.offer(root);
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> list = new ArrayList<>();
            for (int i = 0; i < size; i++) {
                Node node = q.poll();
                list.add(node.val);
                if (node.children != null) {
                    for (Node child : node.children) {
                        q.offer(child);
                    }
                }
            }
            ans.add(list);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution429 solu = new Solution429();
        System.out.println(solu.levelOrder(new Node(1, Arrays.asList(new Node(3), new Node(2), new Node(4)))));
    }
}

class Node {
    public int val;
    public List<Node> children;

    public Node() {}

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};