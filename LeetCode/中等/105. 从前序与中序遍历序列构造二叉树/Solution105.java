/*
url: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
LeetCode参考: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solutions/255811/cong-qian-xu-yu-zhong-xu-bian-li-xu-lie-gou-zao-9/
相关: LeetCode106. 从中序与后序遍历序列构造二叉树, LeetCode889. 根据前序和后序遍历构造二叉树
*/

import java.util.*;

class Solution105 {
	/*public TreeNode buildTree(int[] preorder, int[] inorder) {
	    return myBuildTree(preorder,0,preorder.length-1,inorder,0,inorder.length-1);
	}
	private TreeNode myBuildTree(int[] preorder,int left1,int right1,int[] inorder
	,int left2,int right2){
	    if(right1<left1) return null;
	    int mid1 = left1;
	    int mid2 = 0;//根的下标,不一定真在中间
	    for(int i=left2;i<=right2;i++){
	        if(preorder[mid1]==inorder[i]){
	            mid2 = i;
	        }
	    }
	    int leftTreeSize = mid2 - left2;
	    int rightTreeSize = right2 - mid2;
	    TreeNode root = new TreeNode(preorder[mid1]);
	    root.left = myBuildTree(preorder,left1+1,left1+leftTreeSize,inorder,left2,mid2-1);
	    root.right = myBuildTree(preorder,right1+1-rightTreeSize,right1,inorder,mid2+1,right2);
	    return root;
	}*/
	
	public TreeNode buildTree(int[] preorder, int[] inorder) {
        Deque<TreeNode> stack = new LinkedList<>();
		TreeNode root = new TreeNode(preorder[0]);
		stack.push(root);
		int inorderIndex = 0;
		for (int i = 1; i < preorder.length; i++) {
			TreeNode node = stack.peek();
			if (node.val != inorder[inorderIndex]) { // 构建node的最左侧通路
				node.left = new TreeNode(preorder[i]);
				node = node.left;
				stack.push(node);
			}
			// node.val == inorder[inorderIndex]，已经构建完最左侧通路的最后一个节点，此时需要构建右子树，但是当前节点不一定有右子树，因此可能需要回退多步
			else {
				// 按最左侧通路回退，到第一个有右子树的节点，回退过程会刚好有stack.peek().val == inorder[inorderIndex]，因为inorder访问最左侧通路和刚刚入栈顺序刚好相反
				while (!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
					node = stack.pop();
					inorderIndex++;
				}
				// node现在是第一个有右子树的节点
				node.right = new TreeNode(preorder[i]);
				stack.push(node.right);
			}
		}
		return root;
    }

	public static void main(String[] args) {
		
	}
}

class ListNode {
	int val;
	ListNode next;

	ListNode() {
	}

	ListNode(int val) {
		this.val = val;
	}

	ListNode(int val, ListNode next) {
		this.val = val;
		this.next = next;
	}
}

class TreeNode {
	int val;
	TreeNode left;
	TreeNode right;

	TreeNode() {
	}

	TreeNode(int val) {
		this.val = val;
	}

	TreeNode(int val, TreeNode left, TreeNode right) {
		this.val = val;
		this.left = left;
		this.right = right;
	}
}