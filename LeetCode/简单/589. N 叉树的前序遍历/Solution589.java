/*
url: https://leetcode.cn/problems/n-ary-tree-preorder-traversal/description/?envType=daily-question&envId=2024-02-18
相关: LeetCode144. 二叉树的前序遍历, LeetCode590. N 叉树的后序遍历
题单题解: https://leetcode.cn/problems/n-ary-tree-preorder-traversal/solutions/215212/yi-tao-quan-fa-shua-diao-nge-bian-li-shu-de-wen--3/
标签: 前序遍历, N叉树的前序遍历
*/

import java.util.*;

public class Solution589 {
    public List<Integer> preorder(Node root) {
        List<Integer> ans = new ArrayList<>();
        pre(root, ans);
        return ans;
    }

    private void pre(Node root, List<Integer> ans) {
        if (root == null) return;
        ans.add(root.val);
        if (root.children != null) {
            for (int i = 0; i < root.children.size(); i++) {
                pre(root.children.get(i), ans);
            }
        }
    }

    /* 我的迭代版写法，相比二叉树的前序遍历，需要解决的问题是，Node出栈时，如何知道下一个儿子是几号。
    但是实际运行用时要8ms，递归的写法用时0ms。官方题解的迭代版写法用时也要7ms。
    */
    public List<Integer> preorder_implementation2(Node root) {
        if (root == null) return new ArrayList<>();
        Deque<Node> stack = new LinkedList<>();
        List<Integer> ans = new ArrayList<>();
        Map<Node, Integer> map = new HashMap<>(); // 用map记录node访问完了几个儿子
        Node node = root;
        while (true) {
            while (node != null) {
                ans.add(node.val);
                stack.push(node);
                if (node.children != null && node.children.size() > 0) {
                    Node child = node.children.get(0); // 走最左侧通路
                    map.put(node, 1);
                    node = child;
                }
                else node = null;
            }
            if (stack.isEmpty()) break;
            node = stack.peek();
            if (node.children == null || map.getOrDefault(node, 0) >= node.children.size()) {
                stack.pop(); // 这个节点已经访问完
                node = null; // 上面的while (node != null)不会进去，这样相当于通过while (true) goto回去回退一步
            }
            else { // 转向下一个孩子，然后走最左侧通路
                Node child = node.children.get(map.get(node));
                map.put(node, map.get(node) + 1);
                node = child;
            }
        }
        return ans;
    }

    // 提交记录执行用时分布界面看到的代码示例，很简洁，也不需要一个map，不过用时也要3ms
    public List<Integer> preorder_implementation3(Node root) {
        if (root == null) return new ArrayList<>();
        Deque<Node> stack = new LinkedList<>();
        List<Integer> ans = new ArrayList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            Node node = stack.pop();
            ans.add(node.val); // 先访问根
            if (node.children != null) {
                // 要反过来，这样第一个孩子就是最先处理的
                for (int i = node.children.size() - 1; i >= 0; i--) {
                    stack.push(node.children.get(i));
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution589 solu = new Solution589();
        System.out.println(solu.preorder(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
        System.out.println(solu.preorder_implementation2(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
        System.out.println(solu.preorder_implementation3(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
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
}