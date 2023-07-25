// https://leetcode.cn/problems/convert-sorted-list-to-binary-search-tree/

public class Solution109 {

	public static void main(String[] args) {
		ListNode head = new ListNode(-10);
		ListNode head1 = new ListNode(-3);
		ListNode head2 = new ListNode(0);
		ListNode head3 = new ListNode(5);
		ListNode head4 = new ListNode(9);
		head.next = head1;
		head1.next = head2;
		head2.next = head3;
		head3.next = head4;
		Solution109 solu = new Solution109();
		solu.sortedListToBST(head);

	}

	//先bfs(层序)建树(按完全二叉树的层序遍历顺序建的树)，再dfs(此处实现为先序遍历)填值
	/*public TreeNode sortedListToBST(ListNode head) {
		TreeNode root = new TreeNode();
		TreeNode p = root;
		ListNode node = head;
		Queue<TreeNode> queue = new LinkedList<>();
		queue.add(p);
		while(!queue.isEmpty()) {
			p = queue.poll();
			if(node.next!=null) {
				p.left = new TreeNode();
				node = node.next;
				queue.add(p.left);
			}
			if(node.next!=null) {
				p.right = new TreeNode();
				node = node.next;
				queue.add(p.right);
			}
		}
		dfs(root,head); //先序遍历
		return root;
	}
	
	private void dfs(TreeNode root, ListNode head) {
		if(root==null) {
			return null;
		}
		else {
			dfs(root.left,head);
			root.val = head.val;
			head = head.next;  //这样不行，递归调用把head传进去了并把head本身改变了(非改变head中的属性值)，但父调用中的head没变
			dfs(root.right,head);
		}
	}
	private ListNode dfs(TreeNode root, ListNode head) {
		if(root==null) {
			return head;
		}
		else {
			head = dfs(root.left,head);
			root.val = head.val;
			head = head.next;
			head = dfs(root.right,head);
		}
		return head;
	}*/

	//可以直接把LinkedList转成ArrayList,根据下标创建
	ListNode cursor;
	public TreeNode sortedListToBST(ListNode head) {
		ListNode p = head;
		this.cursor = head;
		int len = 0;
		while(p!=null) {
			p = p.next;
			len++;
		}
		return dfs(0,len);
	}

	//i为当前要为之建立的节点的编号(完全二叉树编号关系)
	private TreeNode dfs(int i, int len) {
		if(i>=len) return null; 
		TreeNode root = new TreeNode();
		root.left = dfs(2*i+1,len);
		root.val = cursor.val;
		cursor = cursor.next;
		root.right  = dfs(2*i+2,len);
		return root;
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