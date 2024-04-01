/*
url: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
LeetCode参考: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solutions/426738/cong-zhong-xu-yu-hou-xu-bian-li-xu-lie-gou-zao-14/
相关: LeetCode105. 从前序与中序遍历序列构造二叉树, LeetCode889. 根据前序和后序遍历构造二叉树, LeetCode331. 验证二叉树的前序序列化, LCR 152. 验证二叉搜索树的后序遍历序列
*/

import java.util.Deque;
import java.util.LinkedList;

class Solution106 {
	/* public TreeNode buildTree(int[] inorder, int[] postorder) {
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
	} */
	
	/* 和LeetCode590. N 叉树的后序遍历postorder_implementation3()类似，后序遍历反过来看就是根-右儿子-左儿子，
	中序反过来看是右-根-左。先序中序重建时是根-左-右和左-根-右，于是和先序中序的重建树便类似了，只是要考虑最右侧通路。
	*/
	public TreeNode buildTree(int[] inorder, int[] postorder) {
	    Deque<TreeNode> stack = new LinkedList<>();
		TreeNode root = new TreeNode(postorder[postorder.length - 1]);
		stack.push(root);
		int inorderIndex = inorder.length - 1;
		TreeNode node = root;
		for (int i = postorder.length - 2; i >= 0; i--) {
			if (node.val != inorder[inorderIndex]) { // 最右侧通路
				node.right = new TreeNode(postorder[i]);
				node = node.right;
				stack.push(node);
			}
			else {
				// 回退到第一个有左子树的节点
				while (!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
					node = stack.pop();
					inorderIndex--;
				}
				node.left = new TreeNode(postorder[i]);
				node = node.left;
				stack.push(node);
			}
		}
		return root;
	}

    public static void main(String[] args) {
        Solution106 solu = new Solution106();
		// 普通用例
		solu.buildTree(new int[]{9,3,15,20,7}, new int[]{9,15,7,20,3});

		// 在做`LeetCodeLCR 152. 验证二叉搜索树的后序遍历序列`时，发现这题代码对非法输入无能为力

		// 这里中序[4,5,6,8,9]，后序[4,9,6,5,8]是非法输入，没有对应的树。但是代码能正常运行，但最终重建的树是错的，且最终inorderIndex != 0
		solu.buildTree(new int[]{4,5,6,8,9}, new int[]{4,9,6,5,8});

		// 这里这个用例是合法输入，最终也能给出正确结果，最终inorderIndex != 0
		solu.buildTree(new int[]{1,2,3,4,5}, new int[]{5,4,3,2,1});

		/* 上面的例子说明，以上代码对于不合法的输入是无法判断的，且上面的例子也说明inorderIndex最终是否为0和重建的树是否正确也没有必然关系，
		不能通过结束时判断inorderIndex是否为0得到结论。
		且可能有用例会导致while循环里inorderIndex为负，代码不能正常运行的，这或许可以通过在while循环条件里判断inorderIndex是否大于等于0解决，
		没去试，但是无论是否能解决，也只能保证算法一定能运行结束，根据上面的例子，重建的树仍然可能是错的。这样一来，似乎就只能在建树之后再去
    	中序和后序遍历一遍确认是否重建出了正确的树。
		总之，以上代码只适用于输入序列保证是树的中序和后序遍历的情况。
		*/
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