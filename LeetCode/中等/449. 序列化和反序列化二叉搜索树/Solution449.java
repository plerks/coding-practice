/*
url: https://leetcode.cn/problems/serialize-and-deserialize-bst/?envType=daily-question&envId=2023-09-04
LeetCode参考: https://leetcode.cn/problems/serialize-and-deserialize-bst/solutions/1479903/xu-lie-hua-he-fan-xu-lie-hua-er-cha-sou-5m9r4/
相关: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
      https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Solution449 {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        preorder(root, list);
        String s = list.toString();
        return s.substring(1, s.length() - 1);
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data.equals("")) {
            return null;
        }
        String[] arr = data.split(", ");
        int[] preorder = new int[arr.length];
        for (int i = 0; i < preorder.length; i++) {
            preorder[i] = Integer.parseInt(arr[i]);
        }
        int[] inorder = preorder.clone();
        Arrays.sort(inorder);
        return buildTree(preorder, inorder);
    }

    public TreeNode deserialize_implementation2(String data) {
        if (data.equals("")) {
            return null;
        }
        String[] arr = data.split(", ");
        int[] preorder = new int[arr.length];
        for (int i = 0; i < preorder.length; i++) {
            preorder[i] = Integer.parseInt(arr[i]);
        }
        Deque<Integer> queue = new LinkedList<>();
        for (int i = 0; i < preorder.length; i++) {
            queue.offer(preorder[i]);
        }
        return construct(Integer.MIN_VALUE, Integer.MAX_VALUE, queue);
    }

    private void preorder(TreeNode root, List<Integer> list) {
        if (root == null) return;
        list.add(root.val);
        preorder(root.left, list);
        preorder(root.right, list);
    }

    // LeetCode105. 从前序与中序遍历序列构造二叉树的代码
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        if(preorder == null || preorder.length == 0) return null;
        Stack<TreeNode> stack = new Stack<>();
        TreeNode root = new TreeNode(preorder[0]);
        stack.push(root);
        int inorderIndex = 0;//构建的最左侧通路的终点
        for(int i = 1; i<preorder.length; i++) {
        	TreeNode node = stack.peek();
        	if(node.val != inorder[inorderIndex]) {
        		node.left = new TreeNode(preorder[i]);
        		stack.push(node.left);
        	}
        	else {
        		//否则此时要退栈，对应中序遍历是从最左下方节点后退的过程(会刚好相等)
        		while(!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
        			node = stack.pop();
        			inorderIndex++;
        		}
        		node.right = new TreeNode(preorder[i]);
        		stack.push(node.right);
        	}
        }
        return root;
    }

    /* 参考https://leetcode.cn/problems/serialize-and-deserialize-bst/solutions/1479903/xu-lie-hua-he-fan-xu-lie-hua-er-cha-sou-5m9r4/，
    由于输入是二叉搜索树，不需要对先序遍历得到的数组排序以得到中序遍历，可以直接根据有序性由先序遍历的数组恢复二叉搜索树
    */
    private TreeNode construct(int lower, int upper, Deque<Integer> queue) {
        if (queue.isEmpty() || queue.peek() < lower || queue.peek() > upper) {
            return null;
        }
        int val = queue.poll();
        TreeNode root = new TreeNode(val);
        root.left = construct(lower, val, queue);
        root.right = construct(val, upper, queue);
        return root;
    }

    public static void main(String[] args) {
        Solution449 solu = new Solution449();
        solu.serialize(null);
    }
}