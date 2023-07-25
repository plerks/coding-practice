/*
url: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
相关: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
*/

import java.util.Stack;

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
        if(preorder==null || preorder.length ==0) return null;
        Stack<TreeNode> stack = new Stack<>();
        TreeNode root=new TreeNode(preorder[0]);
        stack.push(root);
        int inorderIndex = 0;//构建的最左侧通路的终点
        for(int i=1;i<preorder.length;i++) {
        	TreeNode node = stack.peek();
        	if(node.val!=inorder[inorderIndex]) {
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