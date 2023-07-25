/*
url: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
相关: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
*/

class Solution106 {
	public TreeNode buildTree(int[] inorder, int[] postorder) {
		return myBuildTree(inorder,0,inorder.length-1,postorder,0,postorder.length-1);
	}
	private TreeNode myBuildTree(int[] inorder,int left1,int right1,int[] postorder
	,int left2,int right2){
		if(right1<left1) return null;
	    TreeNode root = new TreeNode(postorder[right2]);
	    int mid1 = 0;
	    for(int i=left1;i<=right1;i++) {
	    	if(root.val==inorder[i]) {
	    		mid1 = i;
	    	}
	    }
	    root.left = myBuildTree(inorder,left1,mid1-1,postorder,left2,left2+mid1-1-left1);
	    root.right = myBuildTree(inorder,mid1+1,right1,postorder,right2-right1+mid1,right2-1);
	    return root;
	}
	
	/*public TreeNode buildTree(int[] inorder, int[] postorder) {
	    if(inorder==null || inorder.length ==0) return null;
	    Stack<TreeNode> stack = new Stack<>();
	    TreeNode root=new TreeNode(postorder[postorder.length-1]);
	    stack.push(root);
	    int inorderIndex = inorder.length-1;//构建的最右侧通路的终点
	    for(int i=postorder.length-2;i>=0;i--) {
	    	TreeNode node = stack.peek();
	    	if(node.val!=inorder[inorderIndex]) {
	    		node.right = new TreeNode(postorder[i]);
	    		stack.push(node.right);
	    	}
	    	else {
	    		//否则此时要退栈，对应中序遍历是从最右下方节点后退的过程(会刚好相等)
	    		while(!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
	    			node = stack.pop();
	    			inorderIndex--;
	    		}
	    		node.left = new TreeNode(postorder[i]);
	    		stack.push(node.left);
	    	}
	    }
	    return root;
	}*/

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