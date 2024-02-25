/*
url: https://leetcode.cn/problems/n-ary-tree-postorder-traversal/description/?envType=daily-question&envId=2024-02-19
相关: LeetCode145. 二叉树的后序遍历, LeetCode589. N 叉树的前序遍历
标签: 后序遍历, N叉树的后序遍历
*/

import java.util.*;

// 没N叉树的中序遍历这道题，虽然可以定义访问完半数的子树然后访问根
public class Solution590 {
    public List<Integer> postorder(Node root) {
        List<Integer> ans = new ArrayList<>();
        post(root, ans);
        return ans;
    }

    private void post(Node root, List<Integer> ans) {
        if (root == null) return;
        if (root.children != null) {
            for (Node child : root.children) {
                post(child, ans);
            }
        }
        ans.add(root.val);
    }

    // 和LeetCode589. N 叉树的前序遍历preorder_implementation2()基本相同，只需要改下ans.add(node.val)的位置
    public List<Integer> postorder_implementation2(Node root) {
        if (root == null) return new ArrayList<>();
        Deque<Node> stack = new LinkedList<>();
        List<Integer> ans = new ArrayList<>();
        Map<Node, Integer> map = new HashMap<>(); // 用map记录node访问完了几个儿子
        Node node = root;
        while (true) {
            while (node != null) {
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
                ans.add(node.val);
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

    /* 提交记录执行用时分布界面看到的代码示例，非常非常巧妙。迭代版后序遍历的困难点在于根节点要在访问完子树后访问，因此需要考虑子树访问完成情况，
    LeetCode145. 二叉树的后序遍历postorderTraversal_implementation2()就需要一个prev变量记录刚访问完的子树。
    但是这样实现，可以像先序一样直接先访问根，无需将根的访问延后，避免了这种复杂性，只是最后要反一下。 */
    public List<Integer> postorder_implementation3(Node root) {
        if (root == null) return new ArrayList<>();
        Deque<Node> stack = new LinkedList<>();
        List<Integer> ans = new ArrayList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            Node node = stack.pop();
            // 这样访问顺序是：根-从右到左的子树，刚好和后序遍历相反，因此最后要反一下
            ans.add(node.val);
            if (node.children != null) {
                for (int i = 0; i < node.children.size(); i++) {
                    stack.push(node.children.get(i));
                }
            }
        }
        Collections.reverse(ans);
        return ans;
    }

    public static void main(String[] args) {
        Solution590 solu = new Solution590();
        System.out.println(solu.postorder(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
        System.out.println(solu.postorder_implementation2(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
        System.out.println(solu.postorder_implementation3(new Node(1, Arrays.asList(new Node(3, Arrays.asList(new Node(5), new Node(6))), new Node(2), new Node(4)))));
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